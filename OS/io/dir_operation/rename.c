/*
#include <stdio.h>
int rename(const char *oldpath, const char *newpath);
*/
#include <stdio.h>
int main(){

    int ret = rename("aaa", "ddd");
    if(ret == -1){
        perror("mkdir");
        return -1;
    }

    return 0;
}