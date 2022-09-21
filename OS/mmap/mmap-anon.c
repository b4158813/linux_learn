/*
    匿名映射：不需要文件实体的内存映射
    用于父子间进程通信
*/

#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
int main(){

    // 1. 创建匿名内存映射区
    int len = 4096;
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(ptr == MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    // 2. 父子进程间通信
    pid_t pid = fork();
    if(pid > 0){
        // parent
        strcpy((char *)ptr, "hello world");
        wait(NULL);
    }else if(pid == 0){
        // child
        sleep(1);
        printf("%s\n", (char *)ptr);
    }

    // 3. 释放内存映射区
    int ret = munmap(ptr, len);
    if(ret == -1){
        perror("munmap");
        exit(0);
    }

    return 0;
}