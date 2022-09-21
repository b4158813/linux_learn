#include<stdio.h>
#include "head.h"

int main(){

    int a = 1, b = 2;
    printf("%d + %d = %d\n", a, b, add(a,b));
    printf("%d - %d = %d\n", a, b, subtract(a,b));

    return 0;
}