/*
 * Return value:
 * 1 if sigprocmask(SIG_UNBLOCK) returns w/ SIGTERM pending
 * 2 if sigprocmask(SIG_UNBLOCK) returns w/ SIGTERM *not* pending
 * 90 if exec fails
 *
 * Dies to SIGTERM about half the time, returning 1 the other half.  Compiling
 * with -DREBLOCK makes it die to SIGTERM always.
 */
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    sigset_t set;

    if (argc == 1)
    {
	char *cmd[] = { argv[0], "anything", (char *)0 };

	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
	raise(SIGTERM);

	execv(argv[0], cmd);
	return 90;
    }
    else
    {
	char msg[] = "reached write()\n";

#if REBLOCK
	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
#endif
	write(2, msg, sizeof(msg) - 1);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	sigpending(&set);
	return sigismember(&set, SIGTERM) ? 1 : 2;
    }
}
