#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    sigset_t set;
    char msg[] = "reached write()\n";

    if (argc == 1)
    {
	char *cmd[] = { argv[0], "anything", (char *)0 };

	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
	raise(SIGTERM);

	execv(argv[0], cmd);
	return 1;
    }
    else
    {
	/*
	 * Dies to SIGTERM about half the time, returning 0 the other half.
	 * Compiling with -DREBLOCK makes it die to SIGTERM always.
	 */
#if REBLOCK
	sigemptyset(&set);
	sigaddset(&set, SIGTERM);
	sigprocmask(SIG_BLOCK, &set, NULL);
#endif
	write(2, msg, sizeof(msg) - 1);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	return 0;
    }
}
