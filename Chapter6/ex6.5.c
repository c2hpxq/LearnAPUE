#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    time_t t;
    time(&t);
    struct tm *tmp = localtime(&t);
    char buf[64];
    setenv("TZ", "NZDT", 1);
    strftime(buf, 64, "%a %d %b %Y %T %Z", tmp);
    puts(buf);
    unsetenv("TZ");
    strftime(buf, 64, "%a %d %b %Y %T %Z", tmp);
    puts(buf);

    return 0;
}