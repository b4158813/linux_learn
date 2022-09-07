/*

#include <signal.h>

**以下函数均对自定义信号集操作**

int sigemptyset(sigset_t *set);
    功能：清空信号集中的数据，将信号集中的所有标志位置0
    参数：
        - set：传出参数，需要操作的信号集
    返回值：成功0，失败-1

int sigfillset(sigset_t *set);
    功能：将信号集中的所有标志位置1
    其余同上

int sigaddset(sigset_t *set, int signum);
    功能：设置信号集中的某一个信号对应的标志位为1，表示阻塞该信号
    参数：
        - set：传出参数，需要操作的信号集
        - signum：需要设置阻塞的信号

int sigdelset(sigset_t *set, int signum);
    功能：设置信号集中的某一个信号对应的标志位为0，表示不阻塞该信号
    其余同上

int sigismember(const sigset_t *set, int signum);
    功能：判断某个信号是否阻塞
    参数：
        - set：需要操作的信号集
        - signum：需要判断的信号
    返回值：
        1: signum被阻塞
        0: signum不阻塞
        -1: 调用失败

*/
#include <signal.h>
#include <stdio.h>
int main(){

    // 创建一个信号集
    sigset_t set;

    // 清空信号集的内容
    sigemptyset(&set);

    // 判断 SIGINT 是否在信号集 set 里面
    int ret = sigismember(&set, SIGINT);
    if(ret == 0){
        printf("SIGINT 不阻塞\n");
    }else if(ret == 1){
        printf("SIGINT 阻塞\n");
    }

    // 添加几个信号到信号集中
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    // 判断 SIGINT 是否在信号集中
    ret = sigismember(&set, SIGINT);
    if(ret == 0){
        printf("SIGINT 不阻塞\n");
    }else if(ret == 1){
        printf("SIGINT 阻塞\n");
    }
    // 判断 SIGQUIT 是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0){
        printf("SIGQUIT 不阻塞\n");
    }else if(ret == 1){
        printf("SIGQUIT 阻塞\n");
    }

    // 从信号集中删除一个信号
    sigdelset(&set, SIGQUIT);

    // 判断 SIGQUIT 是否在信号集中
    ret = sigismember(&set, SIGQUIT);
    if(ret == 0){
        printf("SIGQUIT 不阻塞\n");
    }else if(ret == 1){
        printf("SIGQUIT 阻塞\n");
    }

    return 0;
}