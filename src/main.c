#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <signal.h>
#include <zlib.h>
#include <sys/mman.h>
#include "base64.h"
#include "srv.h"

#define CHECK_ERR(err, msg) { \
    if (err != Z_OK) { \
        fprintf(stderr, "%s error: %d\n", msg, err); \
        exit(1); \
    } \
}

char *decrypt(char *data) {

    char *newData = (char *)malloc(strlen(data));
    memset(newData, 0, strlen(data));

    for (int i = 0; i < strlen(data); i++) {
        newData[i] = (data[i] ^ 0x42);
    }

    return newData;
}


struct SOStruct{
    int len; //
    char *buffer;
};

int main(int argc, char *argv[]) {
    signal(SIGCHLD, SIG_IGN);
    printf("Starting server!\n");
    createServer() ;

    return 0;
}
