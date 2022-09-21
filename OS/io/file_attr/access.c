/*

#include <unistd.h>
int access(const char *pathname, int mode);
    作用：判断某文件是否有某种权限，或是否存在
    参数：
        pathname：文件名
        mode:
            R_OK: 是否有读权限
            W_OK: 判断是否有写权限
            X_OK: 判断是否有执行权限
            F_OK: 判断是否存在
    返回值：
        成功返回0， 失败返回-1
*/
#include <unistd.h>
#include <stdio.h>
int main(){

    int ret = access("a.txt", F_OK);
    if(ret == -1){
        perror("access");
        return -1;
    }

    printf("File exists!!!\n");

    return 0;
}