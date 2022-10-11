// TCP通信的服务器端

#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){


    // 1. 创建socket（用于监听的套接字）
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if(lfd == -1){
        perror("socket");
        exit(-1);
    }
    // 2. 绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    // inet_pton(AF_INET, "172.18.0.1", saddr.sin_addr.s_addr);
    saddr.sin_addr.s_addr = INADDR_ANY; // 0.0.0.0
    saddr.sin_port = htons(9999);
    int ret = bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    // 3. 监听
    ret = listen(lfd, 8);
    if(ret == -1){
        perror("listen");
        exit(-1);
    }

    // 4. 接收客户端连接
    struct sockaddr_in clientaddr;
    socklen_t Len = sizeof(clientaddr);
    int cfd = accept(lfd, (struct sockaddr *)&clientaddr, &Len);
    if(cfd == -1){
        perror("accept");
        exit(-1);
    }

    // 输出客户端信息
    char clientIP[16];
    inet_ntop(AF_INET, &clientaddr.sin_addr.s_addr, clientIP, sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip is %s, port is %d\n", clientIP, clientPort);

    // 5. 通信
    // 获取客户端数据
    char recvBuf[1024] = {0};
    while(1){

        int len = read(cfd, recvBuf, sizeof(recvBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv client data: %s\n", recvBuf);
        }else if(len == 0){
            // 客户端已断开连接
            printf("client closed...\n");
            break;
        }

        // 给客户端发送数据
        char *data = "hello, i am server.\n";
        write(cfd, data, strlen(data));

    }

    // 关闭文件描述符
    close(cfd);
    close(lfd);

    return 0;
}