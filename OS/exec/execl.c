/*
#include <unistd.h>

extern char **environ;

int execl(const char *path, const char *arg, ... (char  *) NULL );
    参数：
        - path：需要指定的执行的文件的路径或名称
        - arg：可执行文件的参数列表
            第一个参数一般没什么作用，通常写的时可执行程序名称
            第二个参数开始往后，时程序执行所需要的参数列表
            参数最后需要以NULL结束（哨兵）
    返回值：
        只有当调用失败，才会有返回值，返回-1，并设置errno
        如果调用成功，没有返回值。

int execlp(const char *file, const char *arg, ... (char  *) NULL );
    与上一个区别：会到环境变量中查找可执行文件并执行

int execle(const char *path, const char *arg, ..., (char *) NULL, char * const envp[] );
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execvpe(const char *file, char *const argv[], char *const envp[]);

l(list): 参数地址列表，以空指针结尾
v(vector): 存有各参数地址的指针数组的地址
p(path): 按PATH环境变量指定的目录搜索可执行文件
e(environment): 存有环境变量字符地址的指针数组的地址


#include <unistd.h>
int execve(const char *filename, char *const argv[], char *const envp[]);

*/
#include <unistd.h>
#include <stdio.h>
extern char **environ;
int main(){

    // 创建一个子进程，在子进程中执行exec函数族中的函数
    pid_t pid = fork();
    if(pid > 0){
        // parent
        printf("i am parent process, pid: %d\n", getpid());
        sleep(1);
    }else{
        // child
        // execl("hello", "hello", NULL);
        // execl("/bin/ps", "ps", "aux", NULL);
        execlp("ps", "ps", "aux", NULL);
        printf("i am child process, pid: %d\n", getpid());
    }

    for(int i = 0; i < 3; ++ i){
        printf("i = %d, pid = %d\n", i, getpid());
    }

    return 0;
}