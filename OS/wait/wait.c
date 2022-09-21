/*

#include <sys/types.h>
#include <sys/wait.h>
pid_t wait(int *wstatus);
    功能：等待任意一个子进程结束，如果有一个子进程结束，则回收资源
    参数：int *wstatus
        进程退出时的状态信息，传出参数
    返回值：
        - 成功：返回被回收的子进程的pid
        - 失败：返回 -1（所有子进程都结束，或调用函数失败）

    调用wait函数的进程会被挂起（阻塞），直到它的一个子进程退出或收到一个不能被忽略的信号才能被唤醒（相当于继续执行）
    如果没有子进程，则立刻返回-1
    如果子进程都已结束，则立刻返回-1

pid_t waitpid(pid_t pid, int *wstatus, int options);
    功能：


*/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    // 有一个父进程，创建5个子进程（兄弟）
    pid_t pid;
    for(int i = 0; i < 5; ++ i){
        pid = fork();
        if(pid == 0){
            break;
        }
    }

    if(pid > 0){
        // parent
        while(1){
            printf("parent, pid = %d\n", getpid());
            int st;
            int ret = wait(&st);
            if(ret == -1)
                break;

            if(WIFEXITED(st)){
                // 是不是正常退出
                printf("退出状态码：%d\n", WEXITSTATUS(st));
            }
            if(WIFEXITED(st)){
                // 是不是异常退出
                printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
            }
            printf("child die, pid = %d\n", ret);

            sleep(1);
        }
    }else if(pid == 0){
        // child
        // while(1){
            printf("child, pid = %d\n", getpid());
            sleep(1);
        // }
        exit(1);
    }

    return 0;
}