#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>

void recycleChild(int arg){
    while(1){
        int ret = waitpid(-1, NULL, WNOHANG);
        if(ret == -1){
            // 所有子进程都回收完
            break;
        }else if(ret == 0){
            // 还有子进程活着
            break;
        }else if(ret > 0){
            // 被回收了
            printf("子进程 %d 被回收了\n", ret);
        }
    }
}

int main(){

    // 注册信号捕捉
    struct sigaction act;
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recycleChild;
    sigaction(SIGCHLD, &act, NULL);    

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        return -1;
    }
    
    // 绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        return -1;
    }
    
    // 监听
    ret = listen(lfd, 128);
    if(ret == -1){
        perror("listen");
        return -1;
    }


    // 不断循环等待客户连接
    while(1){
        // 接收连接
        struct sockaddr_in caddr;
        int len = sizeof(caddr);
        int cfd = accept(lfd, (struct sockaddr *)&caddr, &len);
        if(cfd == -1){
            if(errno == EINTR){
                continue;
            }
            perror("accept");
            return -1;
        }

        // 每一个连接进来，创建一个子进程跟客户端通信
        pid_t pid = fork();
        if(pid == 0){
            // 子进程
            // 获取客户端信息
            char cliIP[16];
            inet_ntop(AF_INET, &caddr.sin_addr.s_addr, cliIP, sizeof(cliIP));
            unsigned short cliPort = ntohs(caddr.sin_port);
            printf("client IP is: %s, port is %d\n", cliIP, cliPort);

            // 接收客户端发来的数据
            char recvBuf[1024];
            while(1){
                int len = read(cfd, recvBuf, sizeof(recvBuf));
                if(len == -1){
                    perror("read");
                    return -1;
                }else if(len > 0){
                    printf("recv client: %s\n", recvBuf);
                }else if(len == 0){
                    printf("client closed...\n");
                    break;
                }

                write(cfd, recvBuf, strlen(recvBuf) + 1);
            }
            
            close(cfd);
            exit(0); // 退出当前子进程 
        }
    }

    close(lfd);

    return 0;
}