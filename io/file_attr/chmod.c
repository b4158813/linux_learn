/*

#include <sys/stat.h>
int chmod(const char *pathname, mode_t mode);
    作用：修改文件权限
    参数：
        - pathname：文件路径
        - mode：需要修改的权限，8进制数
    返回值：成功0，失败-1

*/
#include <sys/stat.h>
#include <stdio.h>
int main(){

    int ret = chmod("a.txt", 0644);
    if(ret == -1){
        perror("chmod");
        return -1;
    }
    return 0;
}