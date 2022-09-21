/*

#include <pthread.h>
int pthread_detach(pthread_t thread);
    功能：分离一个线程，被分离的线程在终止时会自动释放资源返回给系统
        1. 不能多次分离，会产生未定义行为
        2. 不能区连接已经分离的线程，否则报错
    参数：
        thread：需要分离的线程id
    返回值：
        成功：0
        失败：错误号

*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *callback(void *arg){
    printf("child thread id: %ld\n", pthread_self());
    return NULL;
}

int main(){


    // 创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);
    if(ret != 0){
        char *errostr = strerror(ret);
        printf("error1: %s\n", errostr);
    }

    // 输出主线程和子线程的ID
    printf("tid: %ld, main thread id: %d\n", tid, pthread_self());

    // 设置子线程分离，分离后子线程结束时结束时的资源就不需主线程释放
    ret = pthread_detach(tid);
    if(ret != 0){
        char *errostr = strerror(ret);
        printf("error2: %s\n", errostr);
    }

    // 设置分离后，对分离的子线程进行连接 pthread_join()
    ret = pthread_join(tid, NULL);
    if(ret != 0){
        char *errostr = strerror(ret);
        printf("error3: %s\n", errostr); // 会报错
    }

    pthread_exit(NULL);

    return 0;
}