#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int mydup2(int fd, int fd2) {
    if (fd==fd2)
        return fd;
    close(fd2);
    long maxFd = sysconf(_SC_OPEN_MAX);
    printf("detect #max-file-descriptor: %ld\n", maxFd);
    if (fd2>=maxFd) {
        printf("exceed with fd2 = %d\n", fd2);
        return -1;
    }

    int *fdArray = malloc(sizeof(int)*maxFd);
    int n;
    printf("Creating placeholder ...\n");
    for (n = 0; ;++n) {
        fdArray[n] = dup(fd);
        printf("%d ", fdArray[n]);
        if (fdArray[n]==fd2)
            break;
    }
    printf("\nClosing placeholder ...\n");
    for (;n--;) {
        printf("%d ", fdArray[n]);
        close(fdArray[n]);
    }
    free(fdArray);
    printf("\nsucc dup2 %d to %d\n", fd, fd2);
    return fd2;
}

void show(int fd, int len) {
    printf("read %d form fd = %d\n", len, fd);
    char buf[10];
    int n = read(fd, buf, len);
    if (n) {
        if (buf[n-1]!='\n')
            buf[n++] = '\n';
        buf[n] = '\0';
        puts(buf);
    }
}

int main() {
    int fd = open("dup2.c", O_RDONLY);
    show(fd, 8);
    int fd2 = 20;
    mydup2(fd, fd2);
    show(fd2, 8);

    return 0;

}