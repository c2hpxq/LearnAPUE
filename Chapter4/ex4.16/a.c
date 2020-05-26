#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    int n = 0;
    while (mkdir("fffffff", 0755)>=0) {
        ++n;
        chdir("fffffff");
    }
    printf("depth: %d\n", n);
    printf("detect PATH_MAX=%ld\n", sysconf(_PC_PATH_MAX));
    int bufsize = 20000;
    char *buf = malloc(bufsize);                                  
    if (getcwd(buf, bufsize))
        printf("cwd: %s, length=%lu\n", buf, strlen(buf));
    else perror("getcwd failed");
    return 0;
}