#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "ztask.h"

void tick_poll(void)
{
    static unsigned long old_msec;
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long msec = tv.tv_usec / 1000;

    if(old_msec != msec) {
        zt_tick();
        old_msec = msec;
    }
}

void hello(void)
{
    static int count = 0;
    printf("Hello, world. %d\n", count++);
    fflush(stdout);
}

void hello2(void)
{
    static int count = 0;
    printf("\t\t\tHello, world2. %d\n", count++);
    fflush(stdout);
}

int main(void)
{
    char zt_mem[64];

    zt_init(zt_mem, 64);

    zt_bind(hello, 50, 1);
    zt_bind(hello2, 80, 1);

    while(1) {
        zt_poll();
        tick_poll();
        usleep(500);
    }

    return 0;
}
