#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid;

    pid = fork();

    if (pid < 0) {
      fprintf(stderr, "Fork Failed");
      return 1;
    }

    else if (pid == 0) {
      printf("This is child\n");
      execl("/bin/ls", "ls", "-l", 0);
    }

    else {
      printf("This is parent\n");
      wait(NULL);
      printf("Child Complete\n");
    }

    return 0;
}
