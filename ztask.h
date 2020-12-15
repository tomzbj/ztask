#ifndef _ZTASK_H
#define _ZTASK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*zt_func_t)(void);

// should be called first
int zt_init(void *zt_mem, int size);

// should be called in main loop
void zt_poll(void);

// repeat: repeat inteval;   en: start immediately or not
int zt_bind(zt_func_t func, int repeat, int en);

// should be called in systick_irqhandler
void zt_tick(void);

void zt_start(int id);
void zt_stop(int id);

#ifdef __cplusplus
}
#endif

#endif
