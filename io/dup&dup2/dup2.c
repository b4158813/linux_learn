/*

#include <unistd.h>
int dup2(int oldfd, int newfd);
    作用：重定向文件描述符
    old 指向 a.txt, newfd 指向 b.txt
    调用函数成功后：newfd 和 b.txt 做close，newfd 指向了 a.txt
    等价于: close(newfd), newfd = dup(oldfd);
    oldfd 必须是一个有效的文件描述符
    oldfd 和 newfd 值相同时，相当于无事发生
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){

    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if(fd == -1){
        perror("open");
        return -1;
    }

    int fd1 = open("2.txt", O_RDWR | O_CREAT, 0664);
    if(fd1 == -1){
        perror("open");
        return -1;
    }

    printf("fd: %d, fd1: %d\n", fd, fd1);

    int fd2 = dup2(fd, fd1);
    if(fd2 == -1){
        perror("dup2");
        return -1;
    }

    // 通过fd1去写数据，实际操作的是1.txt
    char *str = "hello, dup2";
    int len = write(fd1, str, strlen(str));
    if(len == -1){
        perror("write");
        return -1;
    }
    
    printf("fd: %d, fd1: %d, fd2: %d\n", fd, fd1, fd2);

    close(fd);
    close(fd1);

    return 0;
}