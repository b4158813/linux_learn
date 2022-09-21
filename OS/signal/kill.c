/*
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid, int sig);
    功能：给某个进程或进程组id发送某个信号sig
    参数：
        - pid：
            > 0：发送给指定进程
            = 0：发送给进程组所有进程
            = -1： 发送给每一个有权限接受这个信号的进程
            < -1：这个pid=某个进程组的ID取反
        - sig：需要发送的信号编号或宏值（建议用宏值）
    
    kill(getppid(), 9);
    kill(getpid(), 9);

int raise(int sig);
    功能：给当前进程发送信号
    参数：
        - sig：需要发送的信号
    返回值：
        - 成功：0
        - 失败：非0
    等同于 kill(getpid(), sig);

void abort(void);
    - 功能：发送SIGABRT信号给当前进程，杀死当前进程
    kill(getpid(), SIGABRT);

*/
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
int main(){

    pid_t pid = fork();
    if(pid > 0){
        printf("parent\n");
        sleep(2);
        printf("kill child process now\n");
        kill(pid, SIGINT);
    }else if(pid == 0){
        int i = 0;
        for(i=0;i<5;++i){
            printf("child\n");
            sleep(1);
        }
    }


    return 0;
}