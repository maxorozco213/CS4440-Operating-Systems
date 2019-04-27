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

//take given string and reverse it
void* reverseString(void* normalString) {
  char* str = normalString;
  char temp;
  int i, j = 0;

  i=0;
  j=strlen(str)-1;

  while(i<j){
    temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }

  // str = reverseString;
  // printf("\nReverse string is: %s\n", str);
  return NULL;
}

int main(int argc, char *argv[0]) {
  time_t clock;
  char string[256];
  char receiveString[256];
  int clientListen = 0;
  int clientConnect = 0;
  bool run = true;
  pthread_t request;
  struct sockaddr_in serverIP;

  //create the socket
  clientListen = socket(AF_INET, SOCK_STREAM, 0);
  memset(&serverIP, '0', sizeof(serverIP));
  memset(string, '0', sizeof(string));

  //create the socket structure
  serverIP.sin_family = AF_INET;
  serverIP.sin_port = htons(2017);
  serverIP.sin_addr.s_addr = INADDR_ANY;

  //bind the sockets
  bind(clientListen, (struct sockaddr*)&serverIP, sizeof(serverIP));
  //listen for requests from the client
  listen(clientListen, 20);

  //run until stopped and accept requests
  while(run) {
    printf("Server running...\n\n");
    //accept an incoming request
    clientConnect = accept(clientListen, (struct sockaddr*) NULL, NULL);
    printf("Server hit...\n\n");
    recv(clientConnect, receiveString, sizeof(receiveString), 0);
    //create a thread passing in the string from client
    pthread_create(&request, 0, reverseString, receiveString);
    //join the thread and get the result
    pthread_join(request, NULL);
    //write into a buffer (buffer name, size, format, content)
    write(clientConnect, receiveString, strlen(receiveString));
    //close the socket
    close(clientConnect);
    sleep(1);
  }

  return 0;
}
