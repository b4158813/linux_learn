/*
#include <sys/time.h>
int getitimer(int which, struct itimerval *curr_value);

int setitimer(int which, const struct itimerval *new_value, struct itimerval *old_value);
    功能：设定定时器（闹钟），可以替代alarm，精度微秒us， 可以实现周期
    参数：
        - which：定时器以什么时间计时
            ITIMER_REAL：真实时间，时间到达发送SIGALRM（常用）
            ITIMER_VIRTUAL：用户态时间，时间到达发送SIGVTALRM
            ITIMER_PROF：用户态+内核态时间，时间到达发送SIGPROF

        - new_value：设置定时器的属性
        struct itimerval {       // 定时器结构体
               struct timeval it_interval; // 每个阶段的时间，间隔时间
               struct timeval it_value;    // 延迟多长时间执行定时器
           };

        struct timeval {         // 时间的结构体
            time_t      tv_sec;  // 秒数
            suseconds_t tv_usec; // 微秒
        };
        
        - old_value：记录上一次定时的时间参数，一般不使用，指定NULL
    返回值：
        - 成功：0
        - 失败：-1，并设置errno
*/
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

// 过3s后，每隔2s定时一次
int main(){
    struct itimerval new_value;
    // 设置间隔时间
    new_value.it_interval.tv_sec = 2;
    new_value.it_interval.tv_usec = 0;
    // 设置延迟时间，3s后第一次发送信号，然后每隔2s发送一次
    new_value.it_value.tv_sec = 3;
    new_value.it_value.tv_usec = 0;


    int ret = setitimer(ITIMER_REAL, &new_value, NULL);
    printf("定时器开始了。。。\n");
    if(ret == -1){
        perror("setitimer");
        exit(-1);
    }

    getchar();

    return 0;
}