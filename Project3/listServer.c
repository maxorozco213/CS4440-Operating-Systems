#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <pthread.h>

FILE* result;
//take given parameter and tag it on ls
void* showDirectory(void* parameter) {
  char* param = parameter;



  return NULL;
}

int main(int argc, char *argv[0]) {
  time_t clock;
  char string[256];
  char receiveString[256];
  char *buffer;
  int clientListen = 0;
  int clientConnect = 0;
  bool run = true;
  pid_t pid;
  struct sockaddr_in serverIP;

  //create the socket
  clientListen = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverIP, '0', sizeof(serverIP));
  // memset(string, '0', sizeof(string));

  //create the socket structure
  serverIP.sin_family = AF_INET;
  serverIP.sin_port = htons(2017);
  serverIP.sin_addr.s_addr = INADDR_ANY;

  //bind the sockets
  bind(clientListen, (struct sockaddr*)&serverIP, sizeof(serverIP));
  //listen for requests from the client
  listen(clientListen, 2);

  //run until stopped and accept requests
  while(run) {
    printf("Server running...\n\n");
    //accept an incoming request
    clientConnect = accept(clientListen, (struct sockaddr*) NULL, NULL);
    printf("Server hit...\n");
    recv(clientConnect, receiveString, sizeof(receiveString), 0);

    pid = fork();

    if(pid < 0) {
      printf("Fork failed...\n");
      exit(0);
    }
    else if(pid == 0) {
      dup2(clientConnect, 1);
      dup2(clientConnect, 2);
      int out = execlp("/bin/ls", "ls", receiveString, (char*) NULL);

    }
    else {
      wait(NULL);
    }

    //write into a buffer (buffer name, size, format, content)
    write(clientConnect, NULL, strlen(receiveString));
    //close the socket
    close(clientConnect);
    sleep(1);
  }

  return 0;
}
