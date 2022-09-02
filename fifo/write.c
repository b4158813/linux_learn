#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
/*
    有名管道注意事项：
        1. 一个为只读打开一个管道的进程会阻塞，直到另一个进程为只写打卡管道
        2. 一个为只写打开一个管道的进程会阻塞，直到另一个进程为只读打卡管道

    读管道：
        管道中有数据，read返回实际读到的字节数
        管道中无数据：
            写端全关，read返回0（相当于EOF）
            写端未全关，read阻塞等待
    
    写管道：
        管道读端全关，进程异常终止（收到一个SIGPIPE信号）
        管道读端未全关：
            管道已满，write阻塞
            管道未满，write写入数据，并返回实际写入字节数
*/
int main(){

    // 1. 判断文件是否存在
    int ret = access("test", F_OK);
    if(ret == -1){
        printf("管道不存在，创建管道\n");

        // 2. 创建管道文件
        ret = mkfifo("test", 0664);
        if(ret == -1){
            perror("mkfifo");
            exit(0);
        }
    }

    // 3. 以只写方式打开管道
    int fd = open("test", O_WRONLY);
    if(fd == -1){
        perror("open");
        exit(0);
    }

    // 4. 写数据
    for(int i = 0; i < 100; ++ i){
        char buf[1024];
        sprintf(buf, "hello, %d\n", i);
        printf("write data : %s\n", buf);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    close(fd);

    return 0;
};