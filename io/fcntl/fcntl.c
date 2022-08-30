/*
#include <unistd.h>
#include <fcntl.h>
int fcntl(int fd, int cmd, ... );
    参数：
        - fd：需要操作的文件描述符
        - cmd：表示对文件描述符进行如何操作
            - F_DUPFD: 复制文件描述符，复制fd，返回一个新的描述符
                int ret = fcntl(fd, F_DUPFD);
            
            - F_GETFL: 获取文件状态flag
                获取的flag和open函数传递的flag相同
            
            - F_SETFL: 设置文件描述符状态flag
                O_RDONLY, O_WRONLY, O_RDWR, O_CREAT 等不可以被修改
                O_APPEND, O_NONBLOCK 等可修改
                    O_APPEND 表示追加数据
                    O_NONBLOCK 设置成非阻塞

        阻塞和非阻塞：描述的是函数调用行为
*/
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
int main(){

    // 1. 复制文件描述符
    // int fd = open("1.txt", O_RDONLY);
    // int ret = fcntl(fd, F_DUPFD);

    // 2. 修改或获取文件状态flag
    int fd = open("1.txt", O_RDWR);
    if(fd == -1){
        perror("open");
        return -1;
    }

    // 获取文件描述符的状态flag
    int flag = fcntl(fd, F_GETFL);
    if(flag == -1){
        perror("fcntl");
        return -1;
    }
    // 修改文件描述符状态flag，给flag加入O_APPEND标记
    int ret = fcntl(fd, F_SETFL, flag | O_APPEND);
    if(ret == -1){
        perror("fcntl");
        return -1;
    }
    // 追加字符串到文件末尾
    char *str = "nihao";
    write(fd, str, strlen(str));
    close(fd);

    return 0;
}