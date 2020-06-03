#include <stdio.h>

void foo() {
    void ** rbp;
    asm ("mov %%rbp, %0":"=r"(rbp));
    int argc = *(long long *)(*rbp-8);
    char ** argv = *(char ***)(*rbp-16);
    for (int i = 0; i < argc; ++i)
        puts(argv[i]);
}

int main(int argc, char *argv[]) {
    foo();

    return 0;
}