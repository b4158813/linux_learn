#include<stdio.h>
#include<string.h>
int pre[10];
int main(int argc, char *argv[]){
	int n = 10;
	for(int i = 1; i < n; ++ i)
		pre[i] = 1, pre[i] += pre[i-1];
	for(int i = 0; i < n; ++ i)
		printf("%d ", pre[i]);
	return 0;
}
