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

    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    inet_pton(AF_INET, "172.18.0.1",  &saddr.sin_addr.s_addr);

    // 通信
    int num = 0;
    while(1){
        
        // 发送数据
        char sendbuf[128];
        sprintf(sendbuf, "hello, I am client %d\n", num++);
        sendto(fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr *)&saddr, sizeof saddr);
        
        // 接收数据
        int num = recvfrom(fd, sendbuf, sizeof sendbuf, 0, NULL, NULL);

        printf("server say: %s\n", sendbuf);

        sleep(1);
    }

    close(fd);

    return 0;
}