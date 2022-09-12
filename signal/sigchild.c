/*
    SIGCHLD 信号产生的3个条件：
        1. 子进程结束
        2. 子进程暂停了
        3. 子进程继续运行
        都会给父进程发送该信号，父进程默认忽略该信号。

    使用SIGCHLD信号可以解决僵尸进程的问题。

*/


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void myFun(int num){
    printf("捕捉到的信号：%d\n", num);
    // 回收子进程PCB资源
    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret > 0){
            printf("child die, pid = %d\n", ret);
        }else if(ret == 0){
            // 说明还有子进程活着
            break;
        }else if(ret == -1){
            // 没有子进程
            break;
        }
    }
}

int main(){

    // 提前设置好阻塞信号集，阻塞SITCHLD，因为有可能子进程很快结束，父进程还没捕捉到
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGCHLD);
    sigprocmask(SIG_BLOCK, &set, NULL);

    pid_t pid;
    for(int i = 0; i < 20; ++i){
        pid = fork();
        if(pid == 0) break;
    }

    if(pid > 0){
        // parent
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = myFun;
        sigaction(SIGCHLD, &act, NULL);

        // 注册玩信号捕捉后，解除阻塞
        sigprocmask(SIG_UNBLOCK, &set, NULL);
        while(1){
            printf("parent process pid: %d\n", getpid());
            sleep(2);
        }
    }else if(pid == 0){
        // child
        printf("child process pid: %d\n", getpid());
    }


    return 0;
}