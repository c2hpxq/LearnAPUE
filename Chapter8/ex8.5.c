#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(void)
{
	pid_t	pid;

	if (fork() == 0) {			/* child */
		execl("/Users/chenhongcheng/Programming/OSLearning/LearnAPUE/Chapter8/testinterp",
				  "testinterp", "myarg1", "MY ARG2", (char *)0);
        perror("exec fail");
	}
	waitpid(pid, NULL, 0);	/* parent */
	exit(0);
}
