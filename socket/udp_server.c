#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){

    // 创建udp通信socket
    int fd = socket(PF_INET, SOCK_DGRAM, 0);
    if(fd == -1){
        perror("socket");
        exit(-1);
    }

    // 绑定
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = INADDR_ANY;
    int ret = bind(fd, (struct sockaddr *)&saddr, sizeof saddr);
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    // 通信
    while(1){
        
        char recvbuf[128];
        struct sockaddr_in caddr;
        int len = sizeof caddr;
        // 接收数据
        int num = recvfrom(fd, recvbuf, sizeof recvbuf, 0, (struct sockaddr *)&caddr, &len);

        char ipbuf[16];
        printf("client IP: %s, Port: %d\n",
            inet_ntop(AF_INET, &caddr.sin_addr.s_addr, ipbuf, sizeof ipbuf),
            ntohs(caddr.sin_port)
        );

        printf("client say: %s\n", recvbuf);

        // 发送数据
        sendto(fd, recvbuf, strlen(recvbuf) + 1, 0, (struct sockaddr *)&caddr, sizeof caddr);

    }

    close(fd);

    return 0;
}