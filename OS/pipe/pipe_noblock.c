/*

    设置管道非阻塞
    int flags = fcntl(fd[0], F_GETFL); // 获取原来的flag
    flags |= O_NONBLOCK;               // 修改flag的值
    fcntl(fd[0], F_SETFL, flags);      // 设置flag

*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
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
        printf("i am parent process, pid = %d\n", getpid());

        // 关闭写端
        close(pipefd[1]);

        int flags = fcntl(pipefd[0], F_GETFL); // 获取原来的flag
        flags |= O_NONBLOCK;               // 修改flag的值
        fcntl(pipefd[0], F_SETFL, flags);      // 设置flag

        // 从管道读取端读取数据
        char buf[1024] = {0};
        while(1){
            int len = read(pipefd[0], buf, sizeof buf);
            printf("len = %d\n", len);
            printf("parent rcv: %s, pid: %d\n", buf, getpid());
            memset(buf, 0, sizeof buf);
            sleep(1);
        }
    }else if(pid == 0){
        // child
        printf("i am child process, pid = %d\n", getpid());

        // 关闭读端
        close(pipefd[0]);

        // 向管道中写入数据
        char buf[1024] = {0};
        while(1){
            char *str = "hello, i am child";
            write(pipefd[1], str, strlen(str));
            sleep(5);
        }
    }

    return 0;
}