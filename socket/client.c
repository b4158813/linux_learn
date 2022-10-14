// TCP 服务器客户端

#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>

int main(){

    // 1. 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1){
        perror("socket");
        exit(-1);
    }

    // 2. 连接服务器端
    struct sockaddr_in serveraddr;
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(9999);
    inet_pton(AF_INET, "172.18.0.1", &serveraddr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    // 3. 通信
    char recvBuf[1024] = {0};
    int i = 0;
    while(1){

        char data[128];
        sprintf(data, "hello, %d\n", i++);        
        // 给服务端发送数据
        write(fd, data, strlen(data));
        // 读取服务端数据
        int len = read(fd, recvBuf, sizeof(recvBuf));
        if(len == -1){
            perror("read");
            exit(-1);
        }else if(len > 0){
            printf("recv server data: %s\n", recvBuf);
        }else if(len == 0){
            // 服务端已断开连接
            printf("server closed...\n");
            break;
        }

        usleep(1000);
    }

    // 关闭连接
    close(fd);


    return 0;
}