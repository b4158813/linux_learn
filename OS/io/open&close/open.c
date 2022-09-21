/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 打开一个已经存在的文件
int open(const char *pathname, int flags);
    参数：
        - pathname: 要打开的文件路径
        - flags: 对文件的操作权限和其他设置
            O_RDONLY, O_WRONLY, ORDWR
        返回值: 一个新的文件描述符，若失败则返回-1

    errno: 属于Linux系统函数库的全局变量，记录最近的错误号

    #include <stdio.h>
    void perror(const char *s);
        s参数: 用户描述，比如hello，最终输出的是 hello: xxx(实际的错误描述)



// 创建一个新的文件
int open(const char *pathname, int flags, mode_t mode);


*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    
    // 打开一个文件
    int fd = open("a.txt", O_RDONLY);
    if(fd == -1){
        perror("open");
    }
    // 读写操作
    
    // 关闭
    close(fd);

    return 0;
}
