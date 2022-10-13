#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <wait.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>

struct sockInfo{
    int fd; // 通信的文件描述符
    pthread_t tid; // 线程号
    struct sockaddr_in addr; // 客户端信息
};

struct sockInfo sockinfos[128];

void * working(void *arg){
    // 子线程和客户端通信 cfd 客户端信息 线程号
    // 获取客户端信息
    struct sockInfo *pinfo = (struct sockInfo *)arg;
    char cliIP[16];
    inet_ntop(AF_INET, &pinfo->addr.sin_addr.s_addr, cliIP, sizeof(cliIP));
    unsigned short cliPort = ntohs(pinfo->addr.sin_port);
    printf("client IP is: %s, port is %d\n", cliIP, cliPort);

    // 接收客户端发来的数据
    char recvBuf[1024];
    while(1){
        int len = recv(pinfo->fd, recvBuf, sizeof(recvBuf), 0);
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv client: %s\n", recvBuf);
        }else if(len == 0){
            printf("client closed...\n");
            close(pinfo->fd);
            break;
        }
        
        // 转成大写并发送回去
        for(int i=0;i<len;++i){
            recvBuf[i] = toupper(recvBuf[i]);
        }

        int ret = send(pinfo->fd, recvBuf, strlen(recvBuf) + 1, 0);
        if(ret == -1){
            perror("send");
            exit(-1);
        }
    }
    return NULL;
}

int main(){

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        return -1;
    }

    // 设置端口复用
    int optval = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    
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

    // 初始化数据
    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for(int i=0;i<max;++i){
        memset(&sockinfos[i], 0, sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }


    // 不断循环等待客户连接，一旦客户端连接进来，就创建一个子线程进行通信
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

        struct sockInfo *pinfo;
        for(int i=0;i<max;++i){
            // 从数组中找到一个可用的sockInfo元素
            if(sockinfos[i].fd == -1){
                pinfo = &sockinfos[i];
                break;
            }
            if(i == max - 1){
                sleep(1);
                i--;
            }
        }

        pinfo->fd = cfd;
        memcpy(&pinfo->addr, &caddr, len);
        pthread_create(&pinfo->tid, NULL, working, pinfo);
        
        pthread_detach(pinfo->tid);
    }

    close(lfd);

    return 0;
}