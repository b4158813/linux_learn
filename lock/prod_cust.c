/*

    生产者消费者模型(简单版)

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// 创建一个互斥锁
pthread_mutex_t mutex;

struct Node{
    int num;
    struct Node* next;
};

// 头节点
struct Node *head = NULL;

void * producer(void *arg){

    // 不断创建新节点添加到链表中
    while(1){
        pthread_mutex_lock(&mutex);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num: %d, tid: %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        usleep(100);

    }

    return NULL;
}

void * customer(void *arg){

    while(1){
        if(head != NULL){
            pthread_mutex_lock(&mutex);
            struct Node *temp = head;
            head = head->next;
            printf("del node, num: %d, tid: %ld\n", temp->num, pthread_self());
            free(temp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        }
    }

    return 0;
}

int main(){
    
    // 初始化互斥锁
    pthread_mutex_init(&mutex, NULL);

    // 创建5个生产者线程，5个消费者线程
    pthread_t ptids[5], ctids[5];
    for(int i=0;i<5;++i){
        pthread_create(&ptids[i], NULL, producer, NULL);
        pthread_create(&ctids[i], NULL, customer, NULL);
    }

    for(int i=0;i<5;++i){
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }

    while(1) { // 防止提前释放互斥锁
        sleep(10);
    }

    // 释放互斥锁
    pthread_mutex_destroy(&mutex);

    pthread_exit(NULL);

    return 0;
}