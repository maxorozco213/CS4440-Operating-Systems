#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <semaphore.h>


typedef struct Children {
  int tasks;
  int childId;
} Child;

typedef struct Parents {
  int isMother;
  int days;
} Parent;

bool check = true;
sem_t* childSem;
//sem_t child[11];

void* performTasks(void* whichParent) {
  int isMother = *((int*) whichParent);

  if(isMother == 1) {
    printf("Mother succeeded\n");
    sleep(10);
    sem_post(&childSem);
  }
  else if (isMother == 0) {
    printf("Father succeeded\n");

  }

  usleep(500000);
  return NULL;
}

int main(int argc, char *argv[0]) {
  int whichParent;
  pthread_t mother;
  pthread_t father;
  int nDays;

  Parent parent;

  if(argc == 2) {
    printf("Entry is %s\n", argv[1]);
    nDays = atoi(argv[1]);
  }
  else if(argc > 2) {
    printf("Too many arguments.\n");
    exit(0);
  }
  else {
    printf("One int expected.\n");
    exit(0);
  }

  sem_open(&childSem, 0, 1);
  printf("Mother is waking up to take care of the children.\n");

  for(int i = 0; i < nDays; i++) {
    whichParent = 1;
    pthread_create(&mother, 0, performTasks, &whichParent);

    sleep(1);
    sem_wait(&childSem);
    whichParent = 0;
    pthread_create(&father, 0, performTasks, &whichParent);

    pthread_join(mother, NULL);
    pthread_join(father, NULL);

    printf("THIS IS THE END OF DAY %d IN THE LIFE OF MOTHER HUBBARD.\n", i+1);
  }

  sem_close(&childSem);

  // printf("This is the size of children: %d\n", size);

  return 0;
}
