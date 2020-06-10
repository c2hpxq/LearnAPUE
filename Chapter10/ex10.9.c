#include "apue.h"
#include <errno.h>
#include <signal.h>

void
pr_mask(const char *str)
{
	sigset_t	sigset;
	int			errno_save;

	errno_save = errno;		/* we can be called by signal handlers */
	if (sigprocmask(0, NULL, &sigset) < 0) {
		err_ret("sigprocmask error");
	} else {
		printf("%s", str);
        int i;
        for (i = 0; i < __DARWIN_NSIG; ++i)
		if (sigismember(&sigset, i))
			psignal(i, "");

		printf("\n");
	}

	errno = errno_save;		/* restore errno */
}

int main() {
    sigset_t s;
    sigemptyset(&s);
    sigaddset(&s, SIGINT);
    sigprocmask(SIG_SETMASK, &s, NULL);
    pr_mask("hi:");
    return 0;
}