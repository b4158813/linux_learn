/*
    使用多线程实现买票案例
    一共100张票，3个窗口并发卖票
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// 全局变量，所有线程共享这一份资源
int tickets = 1000;

// 创建一个互斥量
pthread_mutex_t mutex;

void *sellticket(void *arg){

    // 卖票
    while(tickets){
        // 加锁
        pthread_mutex_lock(&mutex);

        if(tickets){
            printf("%ld 正在卖第 %d 张门票\n", pthread_self(), tickets);
            tickets--;
        }

        // 解锁
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

int main(){

    // 初始化互斥量
    pthread_mutex_init(&mutex, NULL);

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

    // 释放互斥量资源
    pthread_mutex_destroy(&mutex);

    return 0;
}