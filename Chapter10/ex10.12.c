#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE 1000000000

char buf[BUFSIZE];
time_t t;

void alarm_handler(int signo) {
    time(&t);
    printf("%ld\n", t);
    printf("alarm caught\n");
}

int main() {
    for (int i = 0; i < BUFSIZE; ++i) 
        buf[i] = 'a';
    FILE *f = fopen("largefile", "w");

    signal(SIGALRM, alarm_handler);
    alarm(1);
    time(&t);
    printf("%ld\n", t);
    fwrite(buf, 1, BUFSIZE, f);
    time(&t);
    printf("%ld\n", t);

    return 0;
}