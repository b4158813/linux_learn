/*

// 打开指定目录
#include <sys/types.h>
#include <dirent.h>
DIR *opendir(const char *name)
    参数：
        - name：需要打开的目录名称
    返回值：
        - DIR * 类型：理解为目录流
        错误返回NULL

// 读取目录中的数据
#include <dirent.h>
struct dirent *readdir(DIR *dirp);
    参数：
        - dirp：通过opendir返回的结果
    返回值：
        - struct dirent：代表读取到的文件信息
        读取到了末尾或者失败，返回NULL

// 关闭目录
#include <sys/types.h>
#include <dirent.h>
int closedir(DIR *dirp);

*/

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 用于获取目录下所有普通文件的个数
int getFileNum(char *path){

    // 1. 打开目录
    DIR *dir = opendir(path);
    if(dir == NULL){
        perror("opendir");
        exit(0);
    }
    // 返回值（普通文件的数目）
    int res = 0;
    struct dirent *ptr;
    // 排除 . 和 ..
    while((ptr = readdir(dir)) != NULL){
        char *dname = ptr->d_name;
        if(strcmp(dname, ".") == 0 || strcmp(dname, "..") == 0){
            continue;
        }
        // 判断是普通文件还是目录
        if(ptr->d_type == DT_DIR){
            // 目录，需要继续读取整个目录
            char newpath[256];
            sprintf(newpath, "%s/%s", path, dname);
            res += getFileNum(newpath);
        }
        if(ptr->d_type == DT_REG){
            res ++;
        }
    }
    // 关闭目录
    closedir(dir);

    return res;
}
// 读取某个目录下所有普通文件的个数
int main(int argc, char **argv){

    if(argc < 2){
        printf("%s path\n", argv[0]);
        return -1;
    }

    int num = getFileNum(argv[1]);

    printf("普通文件的个数为：%d\n", num);

    return 0;
}
