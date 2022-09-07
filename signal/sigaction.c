/*
#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    功能：检查或改变信号的处理。信号捕捉
    参数：
        - signum：需要捕捉的信号的编号或宏值（信号的名称）
        - act：捕捉到信号之后的处理动作
        - oldact：上一次对信号捕捉相关的设置，一般不使用，传递NULL
    返回值：
        - 成功：0
        - 失败：-1

    struct sigaction {
        // 函数指针，指向函数就是信号捕捉到之后的处理函数
        void     (*sa_handler)(int);
        // 不常用
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        // 临时阻塞信号集，在信号捕捉函数执行过程中，临时阻塞某些信号
        sigset_t   sa_mask;
        // 使用哪一个信号处理对捕捉到的信号进行处理
        // 这个值可以是0，表示使用sa_handler，也可以是SA_SIGINFO表示使用sa_sigaction
        int        sa_flags;
        // 已被废弃
        void     (*sa_restorer)(void);
    };
*/

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// 过3s后，每隔2s定时一次
void myalarm(int num){ // 自定义回调函数
    printf("捕捉到的信号编号是: %d\n", num);
    printf("xxxxxxxx\n");
}
int main(){
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = myalarm;
    sigemptyset(&act.sa_mask); // 清空临时阻塞信号集
    // 注册信号捕捉
    sigaction(SIGALRM, &act, NULL);
    
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

    while(1) {}

    return 0;
}