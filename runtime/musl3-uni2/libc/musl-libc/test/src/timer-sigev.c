#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void signal_function(union sigval args)
{
    printf("Signal Function Invoked.\n");
}

int main(int argc, char **argv)
{
    struct sigevent event;
    event.sigev_signo = SIGUSR1;
    event.sigev_notify = SIGEV_THREAD;
    event.sigev_notify_attributes = NULL;
    event.sigev_notify_function = signal_function;

    timer_t timer;

    struct timespec interval;
    interval.tv_nsec = 0;
    interval.tv_sec = 0;

    struct timespec value;
    value.tv_nsec = 0;
    value.tv_sec = 5;

    struct itimerspec spec;
    spec.it_interval = interval;
    spec.it_value = value;


    if(timer_create(CLOCK_REALTIME, &event, &timer) != 0)
    {
        fprintf(stderr, "Failed to create time.\n");
        return 1;
    }

    if(timer_settime(timer, 0, &spec, NULL) != 0)
    {
        fprintf(stderr, "Failed to arm timer.\n");
        return 2;
    }

    sleep(5);
    timer_delete(timer);
}
