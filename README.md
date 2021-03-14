## ztask

A very simple timer-based scheduler.

就ztask.h和ztask.c俩文件，五个api.

使用方法: 定义任务函数, 在进入主循环前执行zt_bind即可.

之后在主循环里调用 zt_poll(), 在systick中断里调用zt_tick()， 就行了。

如果需要控制任务启动/停止， 需要用一个变量保存zt_bind的返回值，然后执行zt_start和zt_stop.

main.c是mingw环境下的demo. Windows下没有定时器中断, 用gettimeofday简单模拟了一个.

----------------------

# 工作内存

按[@qiwenmin](https://github.com/qiwenmin)的建议, 改为由用户提供, 于是不需要用宏来定义最大任务数量了, 初始化时提供工作区及其字节数即可. 

注意: 如果不是在main函数里初始化, 需要在char zt_mem[64];前面加上static修饰.

        char zt_mem[64];
        zt_cfg_t cfg;
        cfg.zt_mem = zt_mem;
        cfg.size = 64;

# 计数器变量

 原先是由用户在SysTick_Handler之类场合定时调用zt_tick函数, 这个函数里更新内部定时器变量.
  
[@qiwenmin](https://github.com/qiwenmin) 提出了一个更好的方案, 由用户提供tick函数. 考虑到和旧代码的兼容性, 初始化结构体增加了一个函数指针cfg.zt_tick_f, 如果赋值为NULL, 则使用方式和之前相同. 

或者可以让它指向用户提供的tick函数, 比如Arduino库的millis函数. (millis函数也是用定时器溢出+软件计数实现的, 如果是stm32f072之类有硬件32位定时器的MCU, 则效率更高.)

demo_1和demo_2分别是两种方式的示例, 在windows+mingw平台下编译运行.

