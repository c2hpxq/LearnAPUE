#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd, maxFd;
    while ((fd = open("dup2.c", O_RDONLY))>=0)
        maxFd = fd;
    perror("error encountered: ");
    printf("max fd = %d\n", maxFd);

    return 0;
    
}