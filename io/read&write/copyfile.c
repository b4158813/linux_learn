/*
#include <unistd.h>
ssize_t read(int fd, void *buf, size_t count);
    参数：
        - fd：文件描述符，open得到，通过fd操作某文件
        - buf：需要读取数据存放的地方，数组的地址
        - count：指定数组的大小
    返回值：
        - 成功：
            >0: 返回实际的读取到的字节数
            =0: 文件已经读取完了
        - 失败：
            -1，并设置errno


#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
    参数：
        - fd：文件描述符
        - buf：往磁盘写入的数据，数组
        - count：要写入的数据的实际大小
    返回值：
        - 成功：返回实际写入的字节数
        - 失败：返回-1，并设置errno

*/
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(){

    // 通过open打开english.txt
    int srcfd = open("english.txt", O_RDONLY);
    if(srcfd == -1){
        perror("open");
        return -1;
    }

    // 创建一个新文件（拷贝文件）
    int destfd = open("cpy.txt", O_WRONLY | O_CREAT, 0664);
    if(destfd == -1){
        perror("open");
        return -1;
    }

    // 频繁的读写操作
    char buf[1024] = {0};
    int len = 0;
    while((len = read(srcfd, buf, sizeof buf))>0){
        write(destfd, buf, len);
    }

    // 关闭文件
    close(destfd);
    close(srcfd);


    return 0;
}