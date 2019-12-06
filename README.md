# ztask

A very simple timer-based scheduler.

就ztask.h和ztask.c俩文件，五个api.

使用方法: 定义任务函数, 在进入主循环前执行zt_bind即可.

之后在主循环里调用 zt_poll(), 在systick中断里调用zt_tick()， 就行了。

如果需要控制任务启动/停止， 需要用一个变量保存zt_bind的返回值，然后执行zt_start和zt_stop.

main.c是mingw环境下的demo. Windows下没有定时器中断, 用gettimeofday简单模拟了一个.
