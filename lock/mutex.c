/*
    #include <pthread.h>
    互斥量的类型：pthread_mutex_t

    int pthread_mutex_init(pthread_mutex_t *restrict mutex,
        const pthread_mutexattr_t *restrict attr);
        功能：初始化互斥量
        参数：
            - mutex: 需要初始化的互斥量变量
            - attr: 互斥量相关的属性，NULL
        -restrict: C语言修饰符，被修饰的指针，不能由另一个指针操作
            pthread_mutex_t *restrict mutex = xxx;
            pthread_mutex_t *mutex1 = mutex; // 报错

    int pthread_mutex_destroy(pthread_mutex_t *mutex);
        功能：释放互斥量资源

    int pthread_mutex_lock(pthread_mutex_t *mutex);
        功能：加锁（阻塞，如果有一个线程加锁了，其他线程等待）

    int pthread_mutex_trylock(pthread_mutex_t *mutex);
        功能：尝试加锁（如果加锁失败，会直接返回）

    int pthread_mutex_unlock(pthread_mutex_t *mutex);
        功能：解锁

*/