#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

#define SIZE(x) (sizeof(x)/sizeof(x[0]) + 1);

typedef struct Children {
  int tasks[7];
  int wake;
  int breakfast;
  int school;
  int dinner;
  int bath;
  int book;
  int bed;
  int taskNumber;
  int childId;
} Child;

Child children[11];
int size = SIZE(children);
bool check = true;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t sem;
int pshared = 0;
uint sval = 0;
// int sem_init(sem_t *sem, int pshared, uint sval);

// performWake(Child child) {
//   child.tasks[0] = 1;
// }

void* motherThread(void* days) {
  int day = *((int*) days);
  pthread_mutex_lock(&mutex);
  printf("Mother is waking up to take care of the children.\n");

  for(int i = 0; i < day; i++) {
    for(int j = 0; j < size; j++) {
      // children[j].wake = 1;
      // performWake(children[j]);
      printf("Child %d is being woken up.\n", children[j].childId);
      usleep(500000);
    }
    for(int j = 0; j < size; j++) {
      children[j].breakfast = 1;
      printf("Child %d is being fed breakfast.\n", children[j].childId);
      usleep(500000);
    }
  }

  pthread_mutex_unlock(&mutex);
  printf("This is unlocked.\n");
  usleep(500000);
  pthread_exit(NULL);
}

void* fatherThread() {
  sleep(2);
  printf("**Father trying**\n");
  while(check){
    if(!pthread_mutex_trylock(&mutex)) {
      for(int i = 0; i < size; i++){
        printf("Child %d is being read a book\n", children[i].childId);
        usleep(500000);
      }
      break;
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[0]) {
  pthread_t mother;
  pthread_t father;
  int nDays;

  if(argc == 2) {
    printf("Entry is %s\n", argv[1]);
  }
  else if(argc > 2) {
    printf("Too many arguments.\n");
    exit(0);
  }
  else {
    printf("One int expected.\n");
    exit(0);
  }

  for(int j = 0; j < 7; j++){
    for(int i = 0; i < size; i++) {
      children[i].tasks[j] = 0;
      children[i].childId = i+1;
    }
    // children[i].wake = 0;
    // children[i].breakfast = 0;
    // children[i].school = 0;
    // children[i].dinner = 0;
    // children[i].bath = 0;
    // children[i].book = 0;
    // children[i].bed = 0;
  }

  printf("Task value is: %d\n", children[12].tasks[6]);
  nDays = atoi(argv[1]);
  // sem_init(&sem, 0, 1);
  pthread_create(&mother, 0, motherThread, &nDays);
  pthread_create(&father, 0, fatherThread, NULL);
  pthread_join(mother, NULL);
  pthread_join(father, NULL);

  // printf("This is the size of children: %d\n", size);

  return 0;
}
