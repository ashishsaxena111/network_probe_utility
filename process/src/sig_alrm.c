#include     "process.h"

void
sig_alrm (int signo)
{
    (*pr->fsend) ();

    alarm(1);
    return;
}

