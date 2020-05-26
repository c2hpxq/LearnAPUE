#include <sys/time.h>
#include <sys/stat.h>

int main() {
    struct timeval times[2];
    for (int i = 0; i < 2; ++i) {
        times[i].tv_sec = 0;
        times[i].tv_usec = 0;
    }
    struct stat buf;
    lstat("test", &buf);
    times[1].tv_sec = buf.st_atimespec.tv_sec;
    //times[1].tv_usec = buf.st_atimespec.tv_nsec;
    utimes("test", times);

    return 0;
}