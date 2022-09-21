// 使用文件映射实现文件拷贝功能（通常不会用）

/*

    思路：
        1. 对原始文件进行内存映射
        2. 创建新文件（扩展）
        3. 把新文件数据映射到内存中
        4. 通过内存映射将第一个文件的内存数据拷贝到新文件中
        5. 释放数据

*/
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(){

    // 1. 对原始文件进行内存映射
    int fd = open("english.txt", O_RDWR);
    if(fd == -1){
        perror("open");
        exit(0);
    }

    // 获取原始文件的大小
    int len = lseek(fd, 0, SEEK_END);

    // 2. 创建新文件（扩展）
    int fd1 = open("cpy.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1){
        perror("open");
        exit(0);
    }

    // 对新文件进行扩展
    truncate("cpy.txt", len);
    write(fd1, " ", 1);

    // 3. 分别做内存映射
    void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    void *ptr1 = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
    if(ptr == MAP_FAILED || ptr1 == MAP_FAILED){
        perror("mmap");
        exit(0);
    }

    // 4. 通过内存映射将第一个文件的内存数据拷贝到新文件中
    memcpy(ptr1, ptr, len);

    // 5. 释放资源
    munmap(ptr1, len);
    munmap(ptr, len);
    close(fd1);
    close(fd);

    return 0;
}