#include "apue.h"
#include <signal.h>

int inc(const char *, FILE *);

#define BOUND 20

int main() {
    FILE *f = tmpfile();
    setbuf(f, NULL);
    fprintf(f, "0");
    TELL_WAIT();
    int pid = fork();
    if (pid<0) {
        printf("fork error\n");
        return 0;
    }
    if (pid==0) {
        /* child first*/
        for (;;) {
            int n = inc("child", f);
            TELL_PARENT(getppid());
            if (n>BOUND)
                exit(0);
            WAIT_PARENT();
        }
    }
    else {
        /* parent next */
        for (;;) {
            WAIT_CHILD();
            int n = inc("parent", f);
            TELL_CHILD(pid);
            if (n>BOUND)
                exit(0);
        }
    }

    return 0;
}

int inc(const char *id, FILE *f) {
    int n;
    fseek(f, 0, SEEK_SET);
    fscanf(f, "%d", &n);
    printf("%s: %d+1=", id, n);
    fseek(f, 0, SEEK_SET);
    fprintf(f, "%d", ++n);
    printf("%d\n", n);
    return n;
}