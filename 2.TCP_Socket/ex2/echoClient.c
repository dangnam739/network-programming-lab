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

int sendfile(int s, char *buf, int len){

}

int main(int argc, char **argv)
{
    int sockfd;
    int b;
    char *serIP;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];

    //basic check of the arguments
    //additional checks can be inserted
    if (argc != 2)
    {
        perror("Usage: TCPClient <IP address of the server");
        exit(1);
    }

    //Create a socket for the client
    //If sockfd<0 there was an error in the creation of the socket
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Problem in creating the socket");
        exit(2);
    }

    memset(recvline, '0', sizeof(recvline));

    //Creation of the socket
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr= inet_addr(argv[1]);
    servaddr.sin_port =  htons(SERV_PORT); //convert to big-endian order

    //Connection of the client to the socket
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr))<0) {
        perror("Problem in connecting to the server");
        exit(3);
    }

    FILE *fPtr = fopen("test.png", "rb");
    if(fPtr == NULL){
        perror("Can not open file.");
        exit(3);
    }

    while ((b = fread(sendline, 1, sizeof(sendline), fPtr)) > 0) {
        send(sockfd, sendline, b, 0);

        if (recv(sockfd, recvline, MAXLINE,0) == 0){
        //error: server terminated prematurely
            perror("The server terminated prematurely");
            exit(4);
        }
        // printf("%s", "File received from the server: ");
        // fputs(recvline, stdout);
    }
    puts("File is sent to server");

    fclose(fPtr);

    exit(0);
}
