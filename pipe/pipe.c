/*

#include <unistd.h>
int pipe(int pipefd[2]);
    功能：创建一个匿名管道，用来进程间通信
    参数：
        - int pipefd[2] 这个数组是一个传出参数
        pipefd[0] 读端
        pipefd[1] 写端
    返回值：
        成功0，失败-1

    管道默认阻塞，如果管道中没有数据，read阻塞，如果满了，write阻塞
    注意：匿名管道只能用于具有关系进程之间通信（父子、兄弟 等）

*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

    // 在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret == -1){
        perror("pipe");
        exit(0);
    }
    // 创建子进程
    pid_t pid = fork();
    if(pid > 0){
        // parent
        // 从管道读取端读取数据，同时发送数据
        printf("i am parent process, pid = %d\n", getpid());
        // 关闭写端
        close(pipefd[1]);
        char buf[1024] = {0};
        while(1){
            int len = read(pipefd[0], buf, sizeof buf);
            printf("parent rcv: %s, pid: %d\n", buf, getpid());

            // char *str = "hello, i am parent\n";
            // write(pipefd[1], str, strlen(str));
            // sleep(1);
        }
    }else if(pid == 0){
        // child
        // 向管道中写入数据，同时接受数据
        printf("i am child process, pid = %d\n", getpid());
        // 关闭读端
        close(pipefd[0]);
        char buf[1024] = {0};
        while(1){
            char *str = "hello, i am child";
            write(pipefd[1], str, strlen(str));
            // sleep(1);
            // 注意！这里可能会出现自己读自己写的数据的情况！

            // int len = read(pipefd[0], buf, sizeof buf);
            // printf("child rcv: %s, pid: %d\n", buf, getpid());
            // bzero(buf, 1024);
        }
    }

    return 0;
}