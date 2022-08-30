/*

#include <sys/stat.h>
#include <sys/types.h>
int mkdir(const char *pathname, mode_t mode);
    作用：创建一个目录
    参数：
        - pathname：创建的目录的路径
        - mode：权限，8进制数
    返回值：
        成功0，失败-1

*/
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
int main(){

    int ret = mkdir("aaa", 0777);
    if(ret == -1){
        perror("mkdir");
        return -1;
    }

    return 0;
}