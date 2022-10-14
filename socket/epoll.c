#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>
#include <sys/epoll.h>

int main(){

    // 创建socket
    int lfd = socket(PF_INET, SOCK_STREAM, 0);
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(9999);

    // 绑定
    bind(lfd, (struct sockaddr *)&saddr, sizeof(saddr));

    // 监听
    listen(lfd, 8);

    // 用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);

    // 将监听的文件描述符相关检测信息添加到epoll实例中
    struct epoll_event epev;
    epev.events = EPOLLIN;
    epev.data.fd = lfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);

    struct epoll_event epevs[1024];

    while(1){

        int ret = epoll_wait(epfd, epevs, 1024, -1);
        if(ret == -1){
            perror("epoll_wait");
            exit(-1);
        }

        printf("res = %d\n", ret);

        for(int i = 0; i < ret; ++ i){
            int curfd = epevs[i].data.fd;
            if(curfd == lfd){
                // 监听文件描述符有客户端连接
                struct sockaddr_in caddr;
                int len = sizeof(caddr);
                int cfd = accept(lfd, (struct sockaddr *)&caddr, &len);

                epev.events = EPOLLIN | EPOLLOUT;
                epev.data.fd = cfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }else{
                // 最好对每一种事件做特定处理
                if(epevs[i].events & EPOLLOUT){
                    continue;
                }
                // 有数据到达，需要通信
                char buf[1024] = {0};
                int len = read(curfd, buf, sizeof buf);
                if(len == -1){
                    perror("read");
                    exit(-1);
                }else if(len == 0){
                    printf("client closed...\n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                }else if(len > 0){
                    printf("read buf = %s\n", buf);
                    write(curfd, buf, strlen(buf) + 1);
                }
            }
        }
    }

    close(lfd);
    close(epfd);


    return 0;
}