#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(){

    printf("hello\nworld");

    // exit(0);
    _exit(0); // 未刷新缓冲区，world无法输出

    return 0;
}