#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd = open("seek", O_CREAT|O_TRUNC|O_WRONLY, 0664);
    lseek(fd, 4096*20, SEEK_SET);
    close(fd);

    return 0;
}