/*

#include <pthread.h>
int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
    等待，调用了该函数，线程会阻塞
int pthread_cond_timedwait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
    等待多长时间，调用这个函数，线程会阻塞，直到指定时间结束

int pthread_cond_signal(pthread_cond_t *cond);
    唤醒一个或多个等待的线程
int pthread_cond_broadcast(pthread_cond_t *cond);
    唤醒所有的等待的线程

*/

/*

    生产者消费者模型(简单版)

*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

// 创建一个互斥锁
pthread_mutex_t mutex;
// 创建条件变量
pthread_cond_t cond;

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
        
        // 只要生产了一个，就通知消费者消费
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;
}

void * customer(void *arg){

    while(1){
        pthread_mutex_lock(&mutex);
        if(head != NULL){ // 有数据
            struct Node *temp = head;
            head = head->next;
            printf("del node, num: %d, tid: %ld\n", temp->num, pthread_self());
            free(temp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        }else{ // 没有数据，需要等待
            // 当该函数调用阻塞时，会对互斥锁解锁，当不阻塞向下继续执行时，会重新加锁
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }

    return 0;
}

int main(){

    // 初始化条件变量
    pthread_cond_init(&cond, NULL);
    
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

    // 释放条件变量
    pthread_cond_destroy(&cond);

    pthread_exit(NULL);

    return 0;
}