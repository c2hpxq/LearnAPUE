#include <unistd.h>
#include <stdlib.h>

void foo() {
    vfork();
}
int main() {
    foo();
    exit(0);
}