#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void foo() {
    vfork();
    printf("%d\n", getpid());
}
int main() {
    foo();
    char s[100];
    memset(s, 0, sizeof(s));
    printf("%d: bye\n",getpid());
    _exit(0);
}