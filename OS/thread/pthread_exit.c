/*

#include <pthread.h>
void pthread_exit(void *retval);
    功能：终止当前调用该函数的进程
    参数：
        - retval：指针作为返回值，可以在pthread_join()中获取到

pthread_t pthread_self(void);
    功能：获取当前调用线程的id

int pthread_equal(pthread_t t1, pthread_t t2);
    功能：比较两个线程ID是否相等
    不同操作系统的pthread实现不同，大部分是usigned long，有的是struct

*/
#include <pthread.h>
#include <stdio.h>
#include <string.h>

void *callback(void *arg){
    printf("child thread id: %ld\n", pthread_self());
    return NULL; // pthread_exit(NULL);
}

int main(){

    // 创建一个线程
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, callback, NULL);

    if(ret != 0){
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    // 主线程
    for(int i=0;i<5;++i)
        printf("%d\n", i);
    printf("tid: %ld, main thread id: %ld\n", tid, pthread_self());

    // 让主线程退出，不会影响其他线程
    pthread_exit(NULL);

    printf("main thread exit\n");

    return 0;
}