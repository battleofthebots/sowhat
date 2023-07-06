#include <stdio.h>
#include <stdlib.h>

// this is loaded via dlsym.
extern void update(void) {
    system("id >/tmp/lol");
}
