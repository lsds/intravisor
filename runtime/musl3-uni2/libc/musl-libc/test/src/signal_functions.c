#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>

void sig_handler(int sig, siginfo_t *si, void *ctx)
{
    printf("Inside handler function.\n");
}

int main(int argc, char **argv)
{
	struct sigaction sigact;
    struct sigaction pending;
    struct sigaction dest;
    siginfo_t signalinfo;
    union sigval val;
    struct timespec timeout;

    timeout.tv_sec = 1;
    timeout.tv_nsec = 0;
    val.sival_int = SIGUSR1;

    if(sigemptyset(&sigact.sa_mask) != 0)
    {
        perror("sigemptyset error");
        return 1;
    }

    if(sigisemptyset(&sigact.sa_mask) != 1)
    {
        perror("sigisemptyset error");
        return 2;
    }

    if(sigaddset(&sigact.sa_mask, SIGUSR1) != 0)
    {
        perror("sigaddset error");
        return 3;
    }

    if(sigismember(&sigact.sa_mask, SIGUSR1) != 1)
    {
        perror("sigismemer error");
        return 4;
    }

    if(sigdelset(&sigact.sa_mask, SIGUSR1) != 0)
    {
        perror("sigdelset error");
        return 5;
    }

    if(sigismember(&sigact.sa_mask, SIGUSR1) != 0)
    {
        perror("sigismember error");
        return 6;
    }

    if(sigaddset(&sigact.sa_mask, SIGUSR1) != 0)
    {
        perror("sigaddset error");
        return 7;
    }

    if(sigfillset(&sigact.sa_mask) != 0)
    {
        perror("sigfillset error");
        return 8;
    }

    /* Reset sigset for testing other functions. */
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_flags = sigact.sa_flags | SA_SIGINFO | SA_RESTART;
    sigact.sa_sigaction = sig_handler;

    if(sigaction(SIGUSR1, &sigact, NULL) != 0)
    {
        perror("sigaction error");
        return 9;
    }

    sigaddset(&sigact.sa_mask, SIGUSR1);
    if(sigprocmask(SIG_BLOCK, &sigact.sa_mask, NULL))
    {
        perror("sigprocmask error");
        return 10;
    }

    if(sigqueue(getpid(), SIGUSR1, val) != 0)
    {
        perror("sigqueue error");
        return 11;
    }

    if(sigpending(&pending.sa_mask) != 0)
    {
        perror("sigpending error");
        return 12;
    }

    if(sigismember(&pending.sa_mask, SIGUSR1) != 1)
    {
        perror("sigismember error");
        return 13;
    }

    /* Important to not unblock signal as sigwait functions will not timeout. */
    int signal = 0;
    if(sigwait(&sigact.sa_mask, &signal) !=0)
    {
        perror("sigwait error");
        return 14;
    }

    if(sigqueue(getpid(), SIGUSR1, val) != 0)
    {
        perror("sigqueue error");
        return 15;
    }

    if(sigwaitinfo(&sigact.sa_mask, &signalinfo) == -1)
    {
        perror("sigwaitinfo error");
        return 16;
    }

    if(sigtimedwait(&sigact.sa_mask, &signalinfo, &timeout) != 0)
    {
        /* errno should be EAGAIN as we didn't queue a signal */
        if(errno != EAGAIN)
        {
            perror("sigtimedwait error");
            return 17;
        }
    }

    if(sigaddset(&sigact.sa_mask, SIGUSR1) != 0)
    {
        perror("sigaddset error");
        return 18;
    }

    sigqueue(getpid(), SIGUSR1, val);
    if(sigpending(&pending.sa_mask) != 0)
    {
        perror("sigqueue error");
        return 19;
    }

    if(sigorset(&dest.sa_mask, &sigact.sa_mask, &pending.sa_mask) != 0)
    {
        perror("sigorset error");
        return 20;
    }

    if(sigismember(&dest.sa_mask, SIGUSR1) != 1 )
    {
        perror("sigismember error");
        return 21;
    }

    if(sigandset(&dest.sa_mask, &sigact.sa_mask, &pending.sa_mask) != 0)
    {
        perror("sigandset error");
        return 22;
    }

    if(sigismember(&dest.sa_mask, SIGUSR1) != 1)
    {
        perror("sigismember error");
        return 23;
    }

    psiginfo(&signalinfo, "Message");
    psignal(SIGUSR1, "SIGUSR1: ");

    /* FIX: killing process group will trigger error in test script. */
    // if(killpg(getpgrp(), SIGUSR1) !=0)
    // {
    //     perror("killpg error");
    //     return 23;
    // }

    if(sighold(SIGUSR1) != 0)
    {
        perror("sighold error");
        return 24;
    }

    if(sigrelse(SIGUSR1) != 0)
    {
        perror("sigrelse error");
        return 25;
    }

    /* Reset SIGUSR1 to be blocked to leave a signal pending. */
    sigprocmask(SIG_BLOCK, &sigact.sa_mask, NULL);
    if(raise(SIGUSR1) != 0)
    {
        perror("raise error");
        return 26;
    }

    /* sigpause will not return unless an interrupt occurs. */
    sigpause(SIGUSR1);

    if(sigignore(SIGUSR1) != 0)
    {
        perror("sigignore error");
        return 27;
    }

    return 0;
}
