#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>

#define BUFSIZE 4096

int main(int argc, char *argv[]) {
    if (argc!=3) {
        fprintf(stderr, "usage: cp srcfile dstfile\n");
        return 0;
    }
    int sfd, dfd;
    if ((sfd = open(argv[1], O_RDONLY))<0) {
        perror("open srcfile:");
        return 0;
    }
    if ((dfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0644))<0) {
        perror("open dstfile:");
        return 0;
    }

    struct stat info;
    if (fstat(sfd, &info)<0) {
        return 0;
    }

    ftruncate(dfd, info.st_size);

    char buf[BUFSIZE];
    int n;
    while ((n = read(sfd, buf, BUFSIZE)) > 0) {
        int i;
        for (i = 0; i < n; ++i)
            if (buf[i])
                break;
        if (i==n)
            lseek(dfd, n, SEEK_CUR);
        else write(dfd, buf, n);
    }

    close(sfd);
    close(dfd);

    return 0;

}