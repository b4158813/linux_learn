/*
#include <semaphore.h>

int sem_init(sem_t *sem, int pshared, unsigned int value);
    功能：初始化信号量
    参数：
        - sem：信号量变量的地址
        - pshared：
            - 0：用在线程间
            - 1：用在进程间
        - value：信号量的值

int sem_destroy(sem_t *sem);
    - 释放资源

int sem_wait(sem_t *sem);
    - 对信号量加锁，调用一次对信号量值 - 1，如果值为0则阻塞

int sem_trywait(sem_t *sem);

int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

int sem_post(sem_t *sem);
    - 对信号量解锁，调用一次对信号量的值 + 1
int sem_getvalue(sem_t *sem, int *sval);
*/

/*

    sem_t psem;
    sem_t csem;
    init(psem, 0, 8);
    init(csem, 0, 0);

    producer(){
        sem_wait(&psem);
        sem_post(&csem);
    }

    customer(){
        sem_wait(&csem);
        sem_post(&psem);
    }
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

// 创建一个互斥锁
pthread_mutex_t mutex;

// 创建两个信号量
sem_t psem;
sem_t csem;

struct Node{
    int num;
    struct Node* next;
};

// 头节点
struct Node *head = NULL;

void * producer(void *arg){

    // 不断创建新节点添加到链表中
    while(1){
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 1000;
        printf("add node, num: %d, tid: %ld\n", newNode->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
        usleep(100);
    }

    return NULL;
}

void * customer(void *arg){

    while(1){
        sem_wait(&csem);
        pthread_mutex_lock(&mutex);
        struct Node *temp = head;
        head = head->next;
        printf("del node, num: %d, tid: %ld\n", temp->num, pthread_self());
        free(temp);
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
        usleep(100);
    }

    return 0;
}

int main(){

    // 初始化信号量
    sem_init(&psem, 0, 8);
    sem_init(&csem, 0, 0);

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