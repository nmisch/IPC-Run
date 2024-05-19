#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    sigset_t set;
    char msg[] = "reached write()\n";

    sigemptyset(&set);
    sigaddset(&set, SIGTERM);
    sigprocmask(SIG_BLOCK, &set, NULL);

    raise(SIGTERM);
    write(2, msg, sizeof(msg) - 1);
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    return 0;
}
