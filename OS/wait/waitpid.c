/*

#include <sys/types.h>
#include <sys/wait.h>
pid_t waitpid(pid_t pid, int *wstatus, int options);
    功能：回收指定进程号的子进程，可以设置是否阻塞
    参数：
        - pid:
            pid > 0: 某个子进程的pid
            pid == 0: 回收当前进程组的任意子进程
            pid == -1: 回收任意子进程，相当于 wait()（最常用）
            pid < -1: 回收在|pid|组内的任意子进程
        - options: 设置阻塞或非阻塞
            0: 阻塞
            WNOHANG: 非阻塞
    返回值：
        > 0: 返回子进程id
        == 0: options=WNOHANG， 表示还有子进程活着
        == -1: 错误，或者没有子进程活着了

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
            sleep(1);
            int st;
            // int ret = waitpid(-1, &st, 0);
            int ret = waitpid(-1, &st, WNOHANG);
            if(ret == -1){
                break;
            }else if(ret == 0){
                // 说明还有子进程存在
                continue;
            }else if(ret > 0){
                if(WIFEXITED(st)){
                    // 是不是正常退出
                    printf("退出状态： %d\n", WEXITSTATUS(st));
                }
                if(WIFSIGNALED(st)){
                    // 是不是异常退出
                    printf("被哪个信号干掉了：%d\n", WTERMSIG(st));
                }
                printf("child die, pid = %d\n", ret);
            }

        }
    }else if(pid == 0){
        // child
        while(1){
            printf("child, pid = %d\n", getpid());
            sleep(1);
        }
        exit(0);
    }

    return 0;
}