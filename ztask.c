#include "ztask.h"

typedef struct {
    zt_func_t func;
    unsigned long last_schedule, repeat;
    char en;
} zt_task_t;

static struct {
    unsigned long ticks;
    int num_tasks;
    zt_task_t* tasks;
    int tasks_size;
    unsigned long (*tick_f)(void);
} g;

static unsigned long default_tick_f(void)
{
    return g.ticks;
}

int zt_init(zt_cfg_t* cfg)
{
    g.tasks_size = cfg->size / sizeof(zt_task_t);
    g.tasks = (zt_task_t*)cfg->zt_mem;
    if(cfg->zt_tick_f)
        g.tick_f = cfg->zt_tick_f;
    else
        g.tick_f = default_tick_f;

    return g.tasks_size;
}

void zt_tick(void)
{
    g.ticks++;
}

void zt_poll(void)
{
    int i;
    for(i = 0; i < g.num_tasks; i++) {
        unsigned long curr = g.tick_f();
        if(g.tasks[i].en
            && (curr - g.tasks[i].last_schedule >= g.tasks[i].repeat)) {
            g.tasks[i].last_schedule = curr;
            g.tasks[i].func();
        }
    }
}

void zt_stop(int id)
{
    if(id < g.tasks_size)
        g.tasks[id].en = 0;
}

void zt_start(int id)
{
    if(id < g.tasks_size) {
        if(g.tasks[id].en == 0)
            g.tasks[id].last_schedule = g.tick_f() - g.tasks[id].repeat;    // schedule immediately
        g.tasks[id].en = 1;
    }
}

int zt_bind(zt_func_t func, int repeat, int en)
{
    if(g.num_tasks < g.tasks_size) {
        g.tasks[g.num_tasks].func = func;
        g.tasks[g.num_tasks].repeat = repeat;
        g.tasks[g.num_tasks].last_schedule = g.tick_f() - repeat;
        g.tasks[g.num_tasks].en = en;
        return g.num_tasks++;
    }
    else
        return -1;
}
