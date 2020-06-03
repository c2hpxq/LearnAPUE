#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    if (fork()==0) // child
        exit(0);
    printf("parent\n");
    sleep(20);

    return 0;
}