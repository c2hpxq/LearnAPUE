#include <shadow.h>
#include <stdio.h>

int main() {
    struct spwd* s = getspnam("c2hpxq");
    printf("%s\n", s->sp_pwdp);

    return 0;
}
