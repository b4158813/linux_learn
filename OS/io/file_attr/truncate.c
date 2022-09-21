/*

#include <unistd.h>
#include <sys/types.h>
int truncate(const char *path, off_t length);
    作用：所见或扩展文件尺寸至指定大小
    参数：
        - path：需要修改的文件路径
        - length：需要的最终文件变成的大小
    返回值：
        成功返回0，失败-1
*/
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
int main(){

    int ret = truncate("a.txt", 5);
    if(ret == -1){
        perror("truncate");
        return -1;
    }
    
    return 0;
}