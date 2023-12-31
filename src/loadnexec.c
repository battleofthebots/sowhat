#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <zlib.h>
#include <dlfcn.h>
#include "base64.h"
#include "loadnexec.h"

int mem_dlexec(char *so_buffer, int buffer_size) {

    int fd = memfd_create("SO_MEM", 0);
    if (fd < 0) {
        fprintf(stderr, "Error, could not create memfd memory!");
        exit(1);
    }
    write(fd, so_buffer, buffer_size);

    // obtain file path to in-memory descriptor
    char *path = "/proc/self/fd/";
    int length = strlen(path) + 4;
    char *dl_path = (char *)malloc(length);

    //copy mem fd to dl_path to use for dl_open
    snprintf(dl_path, length, "%s%d", path, fd);
    void *handle = dlopen(dl_path, RTLD_LAZY);
    if (handle == NULL){
        fprintf(stderr, "Could not obtain handle to %s\n", dl_path);
        exit(1);
    }

    // exported symbol MUST be update
    void (*test_ptr)() = dlsym(handle, "update");
    test_ptr();
    dlclose(handle);
    free(dl_path);

    return 0;
}


char *decode_and_decompress(char *buff, int buff_size){

   // char *sharedobject = (char *)malloc(buff_size);
    char sharedobject[buff_size];
    //char *b64_decoded = (char *)malloc(16120);
    char *b64_decoded = base64_decode(buff);

    int cbound = compressBound(buff_size);
    uLong upper = buff_size;
    int res = uncompress((Bytef *)sharedobject,
               &upper,
               (Bytef *)b64_decoded,
               cbound);

    if (res != 0) {
        fprintf(stderr, "Error, could not decompress SO!");
        exit(1);
    }

    // copy decompressed buffer to char pointer and return
    char *tmp = (char *)malloc(buff_size);
    strncpy(tmp, sharedobject, buff_size);

    return tmp;
}
