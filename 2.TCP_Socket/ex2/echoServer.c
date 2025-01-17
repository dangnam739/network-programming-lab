#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define MAXLINE 4096 /*max text line length*/
#define SERV_PORT 3000 /*port*/
#define LISTENQ 8 /*maximum number of client connections */

int main (int argc, char **argv)
{
  int listenfd, connfd, n;
  pid_t childpid;
  socklen_t clilen;
  char buf[MAXLINE];
  struct sockaddr_in cliaddr, servaddr;

  //creation of the socket
  listenfd = socket (AF_INET, SOCK_STREAM, 0);

  memset(&servaddr, '0', sizeof(servaddr));
  memset(buf, '0', sizeof(buf));

  //preparation of the socket address
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);

  bind (listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

  listen (listenfd, LISTENQ);

  printf("%s\n","Server running...waiting for connections.");

  while(1){
    clilen = sizeof(cliaddr);
    connfd = accept (listenfd, (struct sockaddr *) &cliaddr, &clilen);
    printf("%s\n","Received request...");

    FILE *fPtr = fopen("test_receive.png", "wb");

    while ( (n = recv(connfd, buf, MAXLINE,0)) > 0)  {
      // printf("%s","String received from and resent to the client:");
      // puts(buf);
      fwrite(buf, 1, n, fPtr);
      send(connfd, buf, n, 0);
    }
    puts("Received file from client.");

    if (n < 0) {
      perror("Receive error");
      exit(1);
    }
    close(connfd);
    fclose(fPtr);
  }
  //close listening socket
  close (listenfd);
}
