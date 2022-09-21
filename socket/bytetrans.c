#include <arpa/inet.h>
#include <stdio.h>
int main(){

    // htons 转端口
    unsigned short a = 0x0102;
    printf("%04x\n", a);
    unsigned short b = htons(a);
    printf("%04x\n", b);

    printf("=================\n");

    // htonl 转IP
    char buf[4] = {192, 168, 1, 100};
    int num = *(int *)buf;
    int sum = htonl(num);
    unsigned char *p = (char *)&sum;
    printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

    printf("=================\n");

    // ntohl
    unsigned char buf1[4] = {1, 1, 168, 192};
    int num1 = *(int *)buf1;
    int sum1 = ntohl(num1);
    unsigned char *p1 = (unsigned char *)&sum1;
    printf("%d %d %d %d\n", *p1, *(p1+1), *(p1+2), *(p1+3));

    return 0;
}