[TOC]

# Ex6.1

由于查看shadow文件中加密的密码。

> c2hpxq@c2hpxq-virtual-machine:~/playground$ ls -l /etc/shadow
> -rw-r----- 1 root shadow 1272 4月   8 00:53 /etc/shadow

shadow文件的owner是root，从权限上来看，我们作为others对其没有任何权限。只能用sudo让root来代为查看（例如执行cat）



# Ex6.2

目前看来，unix系统设计会为获取重要的系统信息（在这里就是加密用户密码，shadow password file）提供接口。参考6.3节，可以知道用于查看shadow文件内容的api：

```c
#include <shadow.h>
struct spwd *getspnam(const char *name);
```

sudo或者干脆切换到root再编译运行ex6.2.c即可



# Ex6.3

程序见ex6.3.c。



# Ex6.4

程序见ex6.4.c。

在我的机器上，long的长度是4字节，得到的结果为：

- 最早时间：1901-12-14
- 最晚时间：2038-01-19

一旦超过INT_MAX，那么就会从INT_MIN开始计数，也就是时间“绕回到”1901年



# Ex6.5

利用unix的时间api实现一个date，程序见ex6.5.c