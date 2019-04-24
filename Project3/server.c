#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <pthread.h>

int main(int argc, char *argv[0]) {
  time_t clock;
  char string[1025];
  int clientListen = 0;
  int clientConnect = 0;
  bool run = true;
  pthread_t request;
  struct sockaddr_in serverIP;

  //create the socket
  clientListen = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverIP, '0', sizeof(serverIP));
  memset(string, '0', sizeof(string));

  serverIP.sin_family = AF_INET;
  serverIP.sin_port = htons(2017);
  serverIP.sin_addr.s_addr = htonl(INADDR_ANY);
  //bind the sockets
  bind(clientListen, (struct sockaddr*)&serverIP, sizeof(serverIP));
  //listen for requests
  listen(clientListen, 20);

  while(run) {
    printf("Server running...\n\n");
    //accept an incoming request
    clientConnect = accept(clientListen, (struct sockaddr*) NULL, NULL);

    clock = time(NULL);
    snprintf(string, sizeof(string), "%.24s\r\n", ctime(&clock));
    write(clientConnect, string, strlen(string));

    close(clientConnect);
    sleep(1);
    pthread_join(request, NULL);
  }

  return 0;
}
