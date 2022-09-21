#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    printf("before fork: \n");
    pid_t pid = fork();			//进程从当前位置开始分裂为父进程和子进程，分别开始交替向前并发执行，区分在于pid不同
    printf("after fork: \n");
    if (pid == -1) {
        perror("fork");
    }

    if (pid > 0) {
        printf("pid: %d\n", pid);
        //程序在父进程，返回子进程的pid
        printf("this is parent process, pid: %d, ppid: %d\n",  getpid(), getppid());
    } else if (pid == 0){
        //程序在子进程，它没有子进程，返回0
        printf("this is child process, pid: %d, ppid: %d\n",  getpid(), getppid());
    }

    for (int i = 0; i < 5; i++) {
        printf("i: %d, pid: %d\n", i, getpid());
        sleep(1);
    }

    return 0;
}