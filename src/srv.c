#include "srv.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()

#define SA struct sockaddr
#define MAX 50000
#define PORT 1776

struct SOStruct{
    char *len; //
    char *buffer;
};

// Function designed for chat between client and server.
void upload(int connfd) {
    char buff[MAX];
    // infinite loop for chat
    for (;;) {
        bzero(buff, MAX);

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        struct SOStruct so;
        so.len = (char *)malloc(4);
        memset(so.len, 0, 4);

        memcpy(so.len, &buff[0], 4);
        so.buffer = &buff[4]; //

        char *tmpMsg = "Recieved data!";
        write(connfd, tmpMsg, strlen(tmpMsg));
    }
}

/**
 * single-threaded TCP server
 * https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
 */
void createServer() {
    int sockfd, connfd;
    unsigned int len;
    struct sockaddr_in servaddr, cli;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully binded..\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) {
        printf("Listen failed...\n");
        exit(0);
    }
    else {
        printf("Server listening..\n");
    }
    len = sizeof(cli);

    // Fork every new socket connection and pass to upload func
    while(1) {
        // Accept the data packet from client and verification
        connfd = accept(sockfd, (SA*)&cli, &len);
        if (connfd < 0) {
            printf("server accept failed...\n");
            exit(0);
        }
        else {
            printf("server accept the client...\n");
        }

        // fork off new connection
        pid_t childpid;
        if ((childpid = fork()) == 0) {
            upload(connfd);
        }
    }

    // After chatting close the socket
    close(sockfd);
}
