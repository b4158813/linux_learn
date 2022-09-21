/*

#include <pthread.h>
int pthread_join(pthread_t thread, void **retval);
    功能：和一个已经终止的线程进行连接，用于回收子线程资源
        特点：
            该函数是阻塞函数，调用一次只能回收一个子线程
            一般在主线程中使用
    参数：
        - thread: 需要回收的子线程的ID
        - retval: 接收子线程退出时的返回时
    返回值：
        成功：0
        失败：非零，返回的错误号

*/

#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg){
    printf("child thread id: %ld\n", pthread_self());
    sleep(3);
    static int val = 10; // 注意一定不能返回局部变量（子线程栈区在结束后就释放了）
    pthread_exit((void *)&val); // return (void *)&val;
}

int main(){

    // 创建一个子线程
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

    // 主线程调用pthread_join回收子线程资源
    int *thread_retval;
    ret = pthread_join(tid, (void **)&thread_retval);
    if(ret != 0){
        char *errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }
    
    printf("exit data: %d\n", *thread_retval);
    printf("回收子线程资源成功\n");

    // 让主线程退出，不会影响其他线程
    pthread_exit(NULL);
    return 0;
}