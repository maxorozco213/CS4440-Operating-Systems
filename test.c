#include <stdio.h>

int main (int argc, char *argv[]) {
  int c;
  FILE *fp;
  char buff[4096];

  printf("Enter %d somethings ", number);
  scanf("%s", word);
  fp = fopen("test.txt", "r");
  if (fp) {
    while((c = getc(fp)) !=EOF){
      putchar(c);
    }
    fclose(fp);
  }


  // char *fgets( char *buf, int n, FILE *fp );
}
