
共享内存相关的函数
#include <sys/ipc.h>
#include <sys/shm.h>
int shmget(key_t key, size_t size, int shmflg);
    功能：创建一个新的共享内存段，或者获取一个既有得共享内存段得标识
        新创建得内存段中得数据都会被初始化为0
    参数：
        - key: key_t 类型是一个整形，通过这个找到或创建一个共享内存
                一般使用16进制表示，非0
        - size: 共享内存得大小
        - shmflg: 属性
            - 访问权限
            - 附加属性：创建/判断共享内存是否存在
                - 创建：IPC_CREAT
                - 判断是否存在：IPC_EXCL，需要和IPC_CREAT一起使用
            例如：IPC_CREAT | IPC_EXCL | 0664
    返回值：
        成功：>0 返回共性内存引用得ID，之后操作共性内存都是通过这个值
        失败：-1，并设置errno

void *shmat(int shmid, const void *shmaddr, int shmflg);
    功能：和当前的进程进行关联
    参数：
        - shmid: 共享内存的标识，由shmget返回值获取
        - shmaddr: 申请的共享内存的起始地址，指定NULL，内核指定
        - shmflg: 对共享内存的操作
            - 读：SHM_RDONLY，必须要有
            - 读写：0
    返回值：
        成功：返回共享内存的首地址
        失败：(void *) -1

int shmdt(const void *shmaddr);
    功能：解除当前进程和共享内存的关联
    参数：
        - shmaddr：共享内存的首地址
    返回值：
        成功：0
        失败：-1

int shmctl(int shmid, int cmd, struct shmid_ds *buf);
    功能：对共享内存进行操作，共享内存删除才会消失，创建共享内存的进程被销毁了，对共享内存无影响
    参数：
        - shmid：共享内存的ID
        - cmd：
            - IPC_STAT：获取共享内存当前状态
            - IPC_SET：设置共享内存状态
            - IPC_RMID：标记共享内存被销毁
        - buf：需要设置或获取的共享内存的属性信息
            - IPC_STAT：buf存储数据
            - IPC_SET：buf中需要初始化数据，设置到内存中
            - IPC_RMID：没用，NULL

#include <sys/types.h>
#include <sys/ipc.h>
key_t ftok(const char *pathname, int proj_id);
    功能：根据指定的路径名，和int值，生成一个共享内存的key
    参数：
        - pathname: 指定一个存在的路径
        - proj_id: int类型，但是这个系统调用只会使用其中的1个字节
            范围: 0~255, 'a'


问题1. 操作系统如何直到一块共享内存被多少个进程关联？
- 共享内存维护了一个结构体struct shmid_ds，这个结构体中的成员shm_nattach记录了关联的进程个数

问题2. 可不可以对共享内存进行多次删除？
- 可以，因为shmctl标记删除（key设置为0）共享内存，不是直接删除
- 当和共享内存关联的进程数为0时，真正被删除

问题3. 共享内存与内存映射的区别
1. 共享内存可以直接创建，内存映射依赖磁盘文件（匿名映射除外）
2. 共享内存效率更高
3. 内存映射：所有进程操作的时同一块共享内存
   内存映射：每个进程再自己的虚拟地址空间有一个独立的内存
4. 数据安全：
    - 进程突然退出：
        共享内存仍然存在，但内存映射区消失
    - 运行进程的电脑宕机
        共享内存中的数据无了，内存映射区的数据由于磁盘文件中的数据还在，所以仍存在
5. 生命周期
    内存映射区：进程退出，内存映射区销毁
    共享内存：进程退出，共享内存还在，标记删除（所有关联进程数为0），或者关机
            如果一个进程退出，会自动和共享内存取消关联
