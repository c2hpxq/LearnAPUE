#include "apue.h"

#define	BUFFSIZE	100

void handler(int signo) {
    fprintf(stderr, "SIGXFSZ caught!\n");
}

int
main(void)
{
	int		nr;
	char	buf[BUFFSIZE];

    signal_intr(SIGXFSZ, handler);
    struct rlimit r;
    getrlimit(RLIMIT_FSIZE, &r);
    r.rlim_cur = 1024;
    setrlimit(RLIMIT_FSIZE, &r);

	while ((nr = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
        int nw;
		if ((nw = write(STDOUT_FILENO, buf, nr)) != nr) {
            fprintf(stderr, "#expected-written: %d\n", nr);
            fprintf(stderr, "#actually-written: %d\n", nw);
			err_sys("write error");
        }
    }

	if (nr < 0)
		err_sys("read error");

	exit(0);
}