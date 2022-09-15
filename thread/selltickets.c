/*
    使用多线程实现买票案例
    一共100张票，3个窗口并发卖票
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 全局变量，所有线程共享这一份资源
int tickets = 100;

void *sellticket(void *arg){

    // 卖票
    while(tickets > 0){
        usleep(1000);
        printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
        tickets--;
    }

    return NULL;
}

int main(){

    // 创建3个子线程
    pthread_t tid[3];
    for(int i=0;i<3;++i){
        pthread_create(&tid[i], NULL, sellticket, NULL);
    }

    // // 回收子线程的资源，阻塞
    // for(int i=0;i<3;++i){
    //     pthread_join(tid[i], NULL);
    // }

    // 设置线程分离
    for(int i=0;i<3;++i){
        pthread_detach(tid[i]);
    }


    pthread_exit(NULL); // 退出主线程

    return 0;
}