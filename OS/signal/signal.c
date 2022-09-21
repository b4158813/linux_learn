/*

#include <signal.h>
typedef void (*sighandler_t)(int);
sighandler_t signal(int signum, sighandler_t handler);
    功能：设置某个信号的捕捉行为
    参数：
        - signum：要捕捉的信号
        - handler：捕捉到信号如何处理
            - SIG_IGN：忽略信号
            - SIG_DFL：使用信号默认行为
            - 回调函数：由内核调用，程序员只负责写，捕捉到信号后如何处理信号
            回调函数：
                - 需要程序员实现，提前准备好，函数类型根据实际需求，看函数指针定义
                - 不是程序员调用，而是当信号产生由内核调用
                - 函数指针是实现回调的手段，函数实现后，将函数名放到函数指针的位置即可
    返回值：
        成功：返回上一次注册的信号处理函数的地址，第一次调用返回NULL
        失败：返回SIG_ERR，设置错误号


SIGSTOP SIGSTOP 不能被捕捉，不能被忽略

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


    // 注册信号捕捉
    // signal(SIGALRM, SIG_IGN);
    // signal(SIGALRM, SIG_DFL);
    // void (*sighandler_t)(int); 函数指针，int类型参数表叔捕捉到的信号的值
    signal(SIGALRM, myalarm);
    
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