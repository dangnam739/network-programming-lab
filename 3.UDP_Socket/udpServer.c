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

#define SERV_PORT 1255
#define MAXLINE 255
int main()
{
  int sockfd, n;
  socklen_t len[2], len_tmp;
  char mesg[MAXLINE];
  struct sockaddr_in servaddr, cliaddr[2], cliaddr_tmp;
  int client_port[2];
  int clients = 0;

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(SERV_PORT);
  if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))>=0)
  {
    printf("Server is running at port %d\n", SERV_PORT);
  }
  else
  {
    perror("bind failed\n");
    return 0;
  }

  for ( ; ; ) {
    len[0] = sizeof(cliaddr[0]);
    len[0] = sizeof(cliaddr[1]);
    len_tmp = sizeof(cliaddr_tmp);

    n = recvfrom(sockfd, mesg, MAXLINE, 0, (struct sockaddr *)&cliaddr_tmp, &len_tmp);
    mesg[n] = '\0';
    printf("Receiving from port %d...%s\n", htons(cliaddr_tmp.sin_port),mesg);

    //first client
    if(clients == 0){
      cliaddr[0] = cliaddr_tmp;
      client_port[0] = ntohs(cliaddr[0].sin_port);
      clients++;
      printf("Client 1 is connected.Address: %s. Port: %d\n", inet_ntoa(cliaddr[0].sin_addr), client_port[0]);
      sendto(sockfd, "You are the only client.", 30, 0, (struct sockaddr *)&cliaddr_tmp, len_tmp);
    }else if (clients == 1)
    {
      //new or existing
      if(client_port[0] == ntohs(cliaddr_tmp.sin_port)){
        // #send back to client 1 that nobody else connected yet
        sendto(sockfd, "You are the only client.", 30, 0, (struct sockaddr *)&cliaddr[0], len[0]);
        printf("Only client\n");
      }
      else
      {
        cliaddr[1] = cliaddr_tmp;
        client_port[1] = ntohs(cliaddr[1].sin_port);
        clients++;
        printf("Client 2 is connected.Address: %s. Port: %d\n", inet_ntoa(cliaddr[1].sin_addr), client_port[1]);
        sendto(sockfd, mesg, n, 0, (struct sockaddr *)&cliaddr[0], len[0]);
      }
    }else
    {
      //There are 2 clients
      if(client_port[0] == ntohs(cliaddr_tmp.sin_port)){
        printf("Sending message to client 2...%s\n", mesg);
        if(sendto(sockfd, mesg, n, 0, (struct sockaddr *)&cliaddr[1], len[1])==-1) clients--;
      }else
      {
        printf("Sending message to client 1...%s\n", mesg);
        if(sendto(sockfd, mesg, n, 0, (struct sockaddr *)&cliaddr[0], len[0]) == -1) clients--;
      }

    }
  }
  close(sockfd);

  }
