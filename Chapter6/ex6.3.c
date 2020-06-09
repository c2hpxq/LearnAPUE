#include <sys/utsname.h>
#include <stdio.h>

int main() {
    struct utsname u;
    uname(&u);
    puts(u.machine);
    puts(u.nodename);
    puts(u.release);
    puts(u.sysname);
    puts(u.version);

    return 0;
}