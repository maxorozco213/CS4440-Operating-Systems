#include <stdio.h>

int main (int argc, char *argv[]) {
  // char word[80];
  int number = 2345678;
  FILE *fp;
  char buff[255];

  // printf("Enter %d somethings ", number);
  // scanf("%s", word);
  fp = fopen("Users/maximilian/desktop/test.txt", "r");
  fscanf(fp, "%s", buff);
  printf("%s", buff);



  // char *fgets( char *buf, int n, FILE *fp );

  return 0;
}
