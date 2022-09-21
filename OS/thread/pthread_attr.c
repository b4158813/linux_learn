/*

int pthread_attr_init(pthread_attr_t *attr);
    功能：初始化线程属性变量

int pthread_attr_destroy(pthread_attr_t *attr);
    功能：释放线程属性的资源

int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    功能：获取线程分离的状态属性

int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
    功能：设置线程分离的状态属性

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg){
    printf("child thread id: %ld\n", pthread_self());
    return NULL;
}

int main(){

    // 创建一个线程属性变量
    pthread_attr_t attr;
    // 初始化属性变量
    pthread_attr_init(&attr);
    // 设置属性（此处设置线程分离）
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // 获取线程栈大小
    size_t size;
    pthread_attr_getstacksize(&attr, &size);
    printf("thread stack size: %ld\n",size);

    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, &attr, callback, NULL);
    if(ret != 0){
        char *errostr = strerror(ret);
        printf("error1: %s\n", errostr);
    }

    // 输出主线程和子线程的ID
    printf("tid: %ld, main thread id: %d\n", tid, pthread_self());

    // 释放线程属性资源
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    pthread_exit(NULL);

    return 0;
}