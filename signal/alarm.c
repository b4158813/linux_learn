/*

#include <unistd.h>
unsigned int alarm(unsigned int seconds);
    功能：设置定时器（闹钟），函数调用开始倒计时，当倒计时为0时，函数会给当前进程发送SIGALARM信号
    参数：
        - seconds：倒计时时长，单位：秒，如果参数为0，则无效
            取消一个定时器，通过 alarm(0)
    返回值：
        - 之前没有定时器：返回0
        - 之前有定时器：返回剩余时间

SIGALARM：默认终止当前的进程，每一个进程都有且只有一个唯一的定时器
    alarm(10); -> 返回0
    过了1秒
    alarm(5); -> 返回9

alarm是非阻塞的

*/
#include <unistd.h>
#include <stdio.h>
int main(){

    int seconds = alarm(5);
    printf("seconds = %d\n", seconds); // 0
    
    sleep(2);
    seconds = alarm(2); // 不阻塞
    printf("seconds = %d\n", seconds); // 3

    while(1){
        
    }

    return 0;
}