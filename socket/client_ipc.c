#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/un.h>

int main(){

    // 每次运行前清空套接字文件
    unlink("client.sock");

    // 1. 创建套接字
    int cfd = socket(PF_LOCAL, SOCK_STREAM, 0);
    if(cfd == -1){
        perror("socket");
        exit(-1);
    }
    
    // 2. 绑定本地套接字文件
    struct sockaddr_un addr;
    addr.sun_family = AF_LOCAL;
    strcpy(addr.sun_path, "client.sock");
    int ret = bind(cfd, (struct sockaddr *)&addr, sizeof addr);
    if(ret == -1){
        perror("bind");
        exit(-1);
    }

    // 3. 连接服务器
    struct sockaddr_un saddr;
    saddr.sun_family = AF_LOCAL;
    strcpy(saddr.sun_path, "server.sock");
    ret = connect(cfd, (struct sockaddr *)&saddr, sizeof saddr);
    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    printf("server socket filename: %s\n", saddr.sun_path);

    // 通信
    int num = 0;
    while(1){

        char buf[128];
        sprintf(buf, "hello, I am client %d\n", num++);
        send(cfd, buf, strlen(buf) + 1, 0);
        printf("client say: %s\n", buf);
        int len = recv(cfd, buf, sizeof buf, 0);
        if(len == -1){
            perror("send");
            exit(-1);
        }else if(len == 0){
            printf("server closed...\n");
            break;
        }else if(len > 0){
            printf("server say: %s\n", buf);
        }

        sleep(1);
    }

    close(cfd);

    return 0;
}