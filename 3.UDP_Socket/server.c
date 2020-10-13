#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BUFLEN 512
#define PORT 7777

void err(char *str)
{
    perror(str);
    exit(1);
}

int main(void)
{
    struct sockaddr_in my_addr, cli_addr[2], cli_temp;
    int sockfd;
    socklen_t slen[2], slen_temp;
    slen[0] = sizeof(cli_addr[0]);
    slen[1] = sizeof(cli_addr[1]);
    slen_temp = sizeof(cli_temp);
    char buf[BUFLEN];
    int clients = 0;
    int client_port[2];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        printf("test\n");
        err("socket");
    }
    else
    {
        printf("Server : Socket() successful\n");
    }
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr)) == -1)
    {
        err("bind");
    }
    else
    {
        printf("Server : bind() successful\n");
    }

    while (1)
    {
        //receive
        printf("Receiving...\n");
        if (recvfrom(sockfd, buf, BUFLEN, 0, (struct sockaddr *)&cli_temp, &slen_temp) == -1)
            err("recvfrom()");
        if (clients == 0)
        {
            //first connection
            //store the temp connection details to the array
            cli_addr[0] = cli_temp;
            //get client 0 port
            client_port[0] = ntohs(cli_addr[0].sin_port);
            clients++;
            printf("Client 0 connected. Port: %d\n", client_port[0]);
            sendto(sockfd, "You are the only client.", 24, 0, (struct sockaddr *)&cli_temp, slen_temp);
        }
        else if (clients == 1)
        {
            //new or existing
            if (client_port[0] == ntohs(cli_temp.sin_port))
            {
                //send back to client 0 that nobody else connected yet
                sendto(sockfd, "You are the only client.", 24, 0, (struct sockaddr *)&cli_addr[0], slen[0]);
                printf("Only client\n");
            }
            else
            {
                //new connection
                cli_addr[1] = cli_temp;
                client_port[1] = ntohs(cli_addr[1].sin_port);
                clients++;
                printf("GOt second client\n");
                sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr *)&cli_addr[0], slen[0]);
            }
        }
        else
        {
            //there are 2 clients connected here. If we get an error from the sendto then we decrement clients
            if (client_port[0] == ntohs(cli_temp.sin_port))
            {
                //client 0 talking send to client 1
                printf("Sedning message to client 2\n");
                if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr *)&cli_addr[1], slen[1]) == -1)
                {
                    clients--;
                    err("sendto()");
                }
            }
            else
            {
                //client 1 talking send to client 0
                printf("Sending message to client 1\n");
                if (sendto(sockfd, buf, BUFLEN, 0, (struct sockaddr *)&cli_addr[0], slen[0]) == -1)
                {
                    clients--;
                    err("sendto()");
                }
            }
        }
        //printf("Received packet from %s:%d\nData: %s\n",
        //        inet_ntoa(cli_addr[clients].sin_addr), ntohs(cli_addr[clients].sin_port), buf);
    }

    close(sockfd);
    return 0;
}