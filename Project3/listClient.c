#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdbool.h>

int main(int argc, char *argv[0]) {
  int createSocket = 0, n = 0;
  int connectStatus;
  char receiveString[256];
  char* sendString;
  bool run = true;
  struct sockaddr_in serverIP;
  memset(receiveString, '0', sizeof(receiveString));

  //check inputted string from cmd line
  if(argc == 2) {
    printf("Sent string: %s\n", argv[1]);

    sendString = argv[1];
  }
  else if(argc > 2) {
    printf("Too many arguments.\n");
    exit(0);
  }
  else {
    printf("One string expected.\n");
    exit(0);
  }

  if((createSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Socket not created... \n");
    return 1;
  }

  //create socket structure
  serverIP.sin_family = AF_INET;
  serverIP.sin_port = htons(2017); //port forwarded on VM
  serverIP.sin_addr.s_addr = inet_addr("127.0.0.1");
  // serverIP.sin_addr.s_addr = inet_addr("40.114.73.53"); //set to linux VM IP
  //connect to the server
  connectStatus = connect(createSocket, (struct sockaddr *)&serverIP, sizeof(serverIP));

  //check the status of the connection
  if(connectStatus < 0) {
    printf("Connection failed...\n");
    return 1;
  }
  else {
    send(createSocket, sendString, sizeof(sendString), 0);
  }

  //read the response from the server
  while((n = read(createSocket, receiveString, sizeof(receiveString) - 1)) > 0) {
    receiveString[n] = 0;
    if(fputs(receiveString, stdout) == EOF) {
      printf("\nStandard output error\n");
    }

    printf("\n");
  }

  if(n < 0){
    printf("Standard input error.\n");
  }

  return 0;
}
