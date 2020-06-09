#include <time.h>
#include <limits.h>
#include <stdio.h>

int main() {
    time_t arr[] = {INT_MIN, INT_MAX};
    for (int i = 0; i < 2; ++i) {
        time_t t = arr[i];
        struct tm *tmp;
        tmp = localtime(&t);
        char buf[128];
        if (strftime(buf, 128, "%F", tmp) == 0)
            printf("error\n");
        puts(buf);
    }

    return 0;
}