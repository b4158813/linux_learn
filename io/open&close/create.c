/*
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 创建一个新的文件
int open(const char *pathname, int flags, mode_t mode);
    参数：
        - pathname
        - flags(int 4个字节，32位标志位，支持按位或)
            - 必选: O_RDONLY, O_WRONLY, O_RDWR
            - 可选: ..., O_CREAT 文件不存在，创建新文件
        - mode: 8进制数，表示创建出的新文件的操作权限
        最终的权限是：mode & ~umask
        例如： 0777 ->
          & (~0022)
          -------------
              0777 -> 0 111 111 111
          &   0755 -> 0 111 101 101
          --------------------------
              0755 <- 0 111 101 101
        umask的作用就是抹去某些权限

*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h> // close
#include <stdio.h> // perror
int main(){

    // 创建一个新文件
    int fd = open("create.txt", O_RDWR | O_CREAT, 0777);
    if(fd == -1){
        perror("open");
    }
    // 关闭
    close(fd);

    return 0;
}