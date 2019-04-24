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

int main(int argc, char *argv[0]) {
  int createSocket = 0, n = 0;
  char receiveString[1024];
  struct sockaddr_in serverIP;
  memset(receiveString, '0', sizeof(receiveString));

  if((createSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("Socket not created... \n");
    return 1;
  }

  serverIP.sin_family = AF_INET;
  serverIP.sin_port = htons(2017);
  serverIP.sin_addr.s_addr = inet_addr("127.0.0.1");

  if(connect(createSocket, (struct sockaddr *)&serverIP, sizeof(serverIP)) < 0) {
    printf("Connection failed...");
    return 1;
  }

  while((n = read(createSocket, receiveString, sizeof(receiveString) - 1)) > 0) {
    receiveString[n] = 0;
    if(fputs(receiveString, stdout) == EOF) {
      printf("\nStandard output error");
    }

    printf("\n");
  }

  if(n < 0){
    printf("Standard input error.");
  }

  return 0;
}
