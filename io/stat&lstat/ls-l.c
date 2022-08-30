// 模拟实现 ls -l 指令
// -rw-r--r-- 1 root root 12 Aug 30 11:02 a.txt

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
int main(int argc, char **argv){

    // 判断输入参数是否正确
    if(argc < 2){
        printf("%s filename\n", argv[0]);
        return -1;
    }

    // 通过stat函数获取用户传入文件的信息
    struct stat st;
    int ret = stat(argv[1], &st);
    if(ret == -1){
        perror("stat");
        return -1;
    }
    // 获取文件类型和文件权限
    char perms[11] = {0}; // 用于保存文件类型和文件权限的字符串
    switch(st.st_mode & S_IFMT){
        case S_IFLNK:
            perms[0] = 'l';
            break;
        case S_IFDIR:
            perms[0] = 'd';
            break;
        case S_IFREG:
            perms[0] = '-';
            break;
        case S_IFBLK:
            perms[0] = 'b';
            break;
        case S_IFCHR:
            perms[0] = 'c';
            break;
        case S_IFSOCK:
            perms[0] = 's';
            break;
        case S_IFIFO:
            perms[0] = 'p';
            break;
        default:
            perms[0] = '?';
            break;
    }

    // 判断文件访问权限
    char tab[3] = {'x', 'w', 'r'};
    for(int i=0;i<9;++i)
        perms[9-i] = ((st.st_mode>>i)&1) ? tab[i%3] : '-';
    perms[10] = '\0';
    // printf("%s\n", perms);

    // 硬链接数
    int linkNum = st.st_nlink;

    // 判断文件所有者
    char *fileUser = getpwuid(st.st_uid)->pw_name;

    // 文件所在组
    char *fileGrp = getgrgid(st.st_gid)->gr_name;

    // 文件大小
    long int fileSize = st.st_size;

    // 获取修改时间
    char *time = ctime(&st.st_mtime);
    char mtime[512] = {0};
    strncpy(mtime, time, strlen(time)-1);
    char buf[1024];
    sprintf(buf, "%s %d %s %s %ld %s %s", perms, linkNum, fileUser, fileGrp, fileSize, mtime, argv[1]);
    printf("%s\n", buf);

    return 0;
}