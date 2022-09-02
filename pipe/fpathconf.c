/*

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
    // 获取管道大小
    long size = fpathconf(pipefd[0], _PC_PIPE_BUF);
    printf("pipe size = %d\n", size);
    return 0;
}