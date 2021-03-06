#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>

//define the size of the array (x) passed into it
#define SIZE(x) (sizeof(x)/sizeof(x[0]) + 1);

//create a child object with task attributes
typedef struct Children {
  int bath;
  int book;
  int bed;
  int taskNumber;
  int childId;
} Children;

typedef struct Parents {
  int isMother;
  int days;
} Parent;

//Child array of 12 elements
Children children[11];
int size = SIZE(children);
bool check = true;
//initialize the mutex
pthread_mutex_t mother = PTHREAD_MUTEX_INITIALIZER;
static int day;

//starts with the program
void* motherThread() {
  // int day = *((int*) days);
  //mutex is locked
  pthread_mutex_lock(&mother);
  printf("Mother is waking up to take care of the children.\n");
  //modify each chlid in the array
  for(int j = 0; j < size; j++) {
    children[j].bath = 0;
    children[j].book = 0;
    children[j].bed = 0;
    printf("Child %d is being woken up.\n", children[j].childId);
    usleep(50000);
  }
  for(int j = 0; j < size; j++) {
    printf("Child %d is being fed breakfast.\n", children[j].childId);
    usleep(50000);
  }
  for(int j = 0; j < size; j++) {
    printf("Child %d is being sent to school.\n", children[j].childId);
    usleep(50000);
  }
  for(int j = 0; j < size; j++) {
    printf("Child %d is being given dinner.\n", children[j].childId);
    usleep(50000);
  }
  //mutex unlocks and father is now able to access
  pthread_mutex_unlock(&mother);
  for(int j = 0; j < size; j++) {
    children[j].bath = 1;
    printf("Child %d is being given a bath.\n", children[j].childId);
    usleep(50000);
  }

  printf("Mother is going to sleep.\n");
  return NULL;
}

//is sleeping when the program begins
void* fatherThread(void* days) {
  // int dayInt = *((int*) days);
  sleep(2);
  //Father thread first attempt to modify children
  printf("**Father is trying.**\n");
  while(check) {
    //checking if the mutex is unlocked
    if(!pthread_mutex_trylock(&mother)) {
      for(int i = 0; i < size; i++) {
        if(children[i].bath == 1) {
          children[i].book = 1;
          printf("Child %d is being read a book.\n", children[i].childId);
          usleep(50000);
        }
        if(children[i].book == 1) {
          children[i].bed = 1;
          printf("Child %d is being tucked into bed.\n", children[i].childId);
          usleep(50000);
        }
      }
      sleep(2);
      check = false;
    }
  }
  return NULL;
}

int main(int argc, char *argv[0]) {
  pthread_t mother;
  pthread_t father;

  if(argc == 2) {
    printf("Entry is %s\n", argv[1]);
    //convert the argument to an int
    day = atoi(argv[1]);
  }
  else if(argc > 2) {
    printf("Too many arguments.\n");
    exit(0);
  }
  else {
    printf("One int expected.\n");
    exit(0);
  }

  //assign children IDs
  for(int i = 0; i < size; i++) {
    children[i].childId = i+1;
  }

  printf("Mother has %d children.\n", size);
  for(int i = 0; i < day; i++) {
    //create the threads n times
    pthread_create(&mother, 0, motherThread, NULL);
    pthread_create(&father, 0, fatherThread, NULL);
  }

  for(int i = 0; i < day; i++) {
    //join the threads
    pthread_join(mother, NULL);
    pthread_join(father, NULL);
  }

  return 0;
}
