#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>

void create_fifo(const char *str){
    int ret = access(str, F_OK);
    if(ret == -1){
        printf("%s 不存在，创建 %s\n", str, str);
        ret = mkfifo(str, 0664);
        if(ret == -1){
            perror("mkfifo");
            exit(-1);
        }
    }
}

int main(){

    // 创建fifo管道
    create_fifo("fifo1");
    create_fifo("fifo2");

    // fork出一个子进程
    pid_t pid = fork();
    int fd1, fd2;
    if(pid > 0){
        // 父进程以只读方式打开1
        fd1 = open("fifo1", O_RDONLY);
        if(fd1 == -1){
            perror("open");
            exit(-1);
        }
        printf("打开fifo1成功，等待读取...\n");
    }else if(pid == 0){
        // 子进程以只写方式打开2
        fd2 = open("fifo2", O_WRONLY);
        if(fd2 == -1){
            perror("open");
            exit(-1);
        }
        printf("打开fifo2成功，等待读取...\n");
    }else{
        perror("fork");
        exit(-1);
    }

    char buf[128];
    int ret;
    while(1){
        if(pid > 0){
            // 父进程循环读fifo1
            memset(buf, 0, sizeof buf);
            ret = read(fd1, buf, 127);
            if(ret <= 0){
                perror("read");
                break;
            }
            printf("buf: %s\n", buf);
        }else if(pid == 0){
            // 子进程循环写fifo2
            memset(buf, 0, sizeof buf);
            fgets(buf, 128, stdin);
            ret = write(fd2, buf, strlen(buf));
            if(ret == -1){
                perror("write");
                exit(-1);
            }
        }
    }

    if(pid > 0) close(fd1);
    if(pid == 0) close(fd2);

    return 0;
}