#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("dup2.c", O_RDONLY);
    int fd2 = 12800;
    int res = dup2(fd, fd2);
    perror("error encountered: ");
    printf("%d\n", res);

    return 0;
    
}