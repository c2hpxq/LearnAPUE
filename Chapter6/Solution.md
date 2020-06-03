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