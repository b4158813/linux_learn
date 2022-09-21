/*

#include <pthread.h>
int pthread_cancel(pthread_t thread);
    功能：取消线程（让线程终止）
         取消某个线程，可以终止某个线程的运行
         但并不是立刻终止，而是到取消点终止

         取消点：系统规定好的一些系统调用
         可粗略地理解为从用户态到内核态的切换这一点
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void *callback(void *arg){
    printf("child thread id: %ld\n", pthread_self());
    for(int i=0;i<5;++i){
        printf("child: %d\n", i);
    }
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

    // 取消线程
    pthread_cancel(tid);

    for(int i=0;i<5;++i){
        printf("parent: %d\n", i);
    }

    // 输出主线程和子线程的ID
    printf("tid: %ld, main thread id: %d\n", tid, pthread_self());

    // 退出主线程
    pthread_exit(NULL);

    return 0;
}