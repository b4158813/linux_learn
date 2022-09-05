/*

#include <sys/mman.h>
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    - 功能：将一个文件或者设备数据映射到内存中
    - 参数：
        - void *addr: NULL, 由内核指定
        - length: 要映射的数据长度，不能为0，建议使用文件长度
                获取文件长度：stat lseek
        - prot: 对申请的内存映射区的操作权限
                - PROT_EXEC: 可执行权限
                - PROT_READ:读权限
                - PROT_WRITE: 写权限
                - PROT_NONE: 没有权限
                要操作内存映射，必须要有读权限
                PROT_READ、PROT_READ|PROT_WRITE
        - flags:
                - MAP_SHARED: 映射区的数据会自动和磁盘文件进行同步，进程间通信，必须要设置此选项
                - MAP_PRIVE: 不同步，内存映射区数据被改变，对原来的文件不修改，会重新创建新文件（写时复制）
        - fd: 需要映射的文件的文件描述符
                - 通过open得到（一个磁盘文件）
                - 注意：文件大小不能为0，open指定的权限不能和prot参数冲突
        - offset：偏移量，一般不用。必须指定4k的整数倍，0表示不便宜
    返回值：返回创建的内存的首地址
        失败返回MAP_FAILED,. (void*)-1
        

int munmap(void *addr, size_t length);
        功能：释放内存映射
        参数：
            - addr：要释放的内存的首地址
            - length：要释放的内存大小，要和mmap函数中的legnth参数值一样
*/

/*
	使用内存映射实现进程间通信：
	1. 有关系的进程（父子进程）
		- 还没有子进程的时候
			- 通过唯一的父进程，先创建内存映射区
		- 有了内存映射区后，创建子进程
		- 父子进程共享创建的内存映射区
	
	2. 没有关系的进程间通信
		- 准备一个大小不是0的磁盘文件
		- 进程1 通过磁盘文件创建内存映射区
			- 得到一个操作这块内存的指针
		- 进程2 通过磁盘文件创建内存映射区
			- 得到一个操作这块内存的指针
		- 使用映射区通信
	
	注意：内存映射区通信，是非阻塞的
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <wait.h>
int main(){

	// 1. 打开一个文件
	int fd = open("test.txt", O_RDWR);
	int size = lseek(fd, 0, SEEK_END);

	// 2. 创建内存映射区
	void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(ptr == MAP_FAILED){
		perror("mmap");
		exit(0);
	}

	// 3. 创建子进程
	pid_t pid = fork();
	if(pid > 0){
		wait(NULL);
		// parent
		char buf[64];
		strcpy(buf, (char *)ptr);
		printf("read data: %s\n", buf);
	}else if(pid == 0){
		// child
		strcpy((char *)ptr, "nihao a, son!!");
	}
	
	// 关闭内存映射区
	munmap(ptr, size);

	return 0;

}