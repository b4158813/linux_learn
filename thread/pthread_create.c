/*

    一般情况下，main函数所在线程称为主线程（main线程），其余创建的线程成为子线程

    程序中默认只有一个进程，fork()函数调用 -> 2个进程
    程序中默认只有一个线程，pthread_create()函数调用 -> 2个线程

    #include <pthread.h>
    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                        void *(*start_routine) (void *), void *arg);
        功能：创建一个子线程
        参数：
            - thread: 传出参数，线程创建成功后，子线程的ID被写到该文档中
            - attr: 设置线程属性，一般使用NULL默认值
            - start_routine: 函数指针，这个函数是子线程需要处理的逻辑代码
            - arg: 给start_routine使用，传参
        返回值：
            成功：0
            失败：返回错误号（与errno不同，char *strerror(int errnum);

*/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

void *callback(void *arg){
    printf("child thread...\n");
    printf("arg value: %d\n", *(int *)arg);
    return NULL;
}

int main(){

    pthread_t tid;
    int num = 10;
    int ret = pthread_create(&tid, NULL, callback, (void *)&num);
    if(ret != 0){
        char * errstr = strerror(ret);
        printf("error: %s\n", errstr);
    }

    for(int i=0;i<5;++i){
        printf("%d\n", i);
    }

    sleep(1);

    return 0; // exit(0)
}