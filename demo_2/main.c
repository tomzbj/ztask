#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "ztask.h"

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

unsigned long tick_func(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

int main(void)
{
    char zt_mem[64];
    zt_cfg_t cfg;
    cfg.zt_mem = zt_mem;
    cfg.size = 64;
    cfg.zt_tick_f = tick_func;

    zt_init(&cfg);
    zt_bind(hello, 500, 1);
    zt_bind(hello2, 1500, 1);

    while(1) {
        zt_poll();
        usleep(500);
    }

    return 0;
}
