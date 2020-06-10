#include "apue.h"
#include <time.h>

int main() {
    int i;
    for (i = 0;;i++) {
        sleep(60);
        if (i%5==0) {
            time_t t;
            time(&t);
            struct tm *tbreak = localtime(&t);
            printf("tm_sec = %d\n", tbreak->tm_sec);
        }
    }

    return 0;
}