#include "ztask.h"

typedef struct {
    zt_func_t func;
    unsigned long last_schedule, repeat;
    char en;
} zt_task_t;

static struct {
    unsigned long ticks;
    int num_tasks;
    zt_task_t *tasks;
    int tasks_size;
} g;

int zt_init(void *zt_mem, int size) {
    g.tasks_size = size / sizeof(zt_task_t);
    g.tasks = (zt_task_t *)zt_mem;

    return g.tasks_size;
}

void zt_tick(void)
{
    g.ticks++;
}

void zt_poll(void)
{
    int i;
    for (i = 0; i < g.num_tasks; i++) {
        if (g.tasks[i].en && (g.ticks - g.tasks[i].last_schedule >= g.tasks[i].repeat)) {
            g.tasks[i].last_schedule = g.ticks;
            g.tasks[i].func();
        }
    }
}

void zt_stop(int id)
{
    if (id < g.tasks_size)
        g.tasks[id].en = 0;
}

void zt_start(int id)
{
    if (id < g.tasks_size) {
        if (g.tasks[id].en == 0)
            g.tasks[id].last_schedule = g.ticks - g.tasks[id].repeat; // schedule immediately
        g.tasks[id].en = 1;
    }
}

int zt_bind(zt_func_t func, int repeat, int en)
{
    if (g.num_tasks < g.tasks_size) {
        g.tasks[g.num_tasks].func = func;
        g.tasks[g.num_tasks].repeat = repeat;
        g.tasks[g.num_tasks].last_schedule = g.ticks - repeat;
        g.tasks[g.num_tasks].en = en;
        return g.num_tasks++;
    }
    else
        return -1;
}
