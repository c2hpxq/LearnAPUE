[TOC]

# Ex4.1

stat会follow symbolic link，所以查看的总是最终指向的文件的状态。也因此，st_mode应永不会为symlink

ex4.1程序查看当前目录下的普通文件file和指向file的symlink，查询到的都是regular file类型

```shell
$ ./a.out file symlink
file: regular
symlink: regular
```

# Ex4.2

创建的所有新文件和文件夹的所有权限位都为0

# Ex4.4

creat(path mode)等价于open(path, O_WRONLY|O_CREAT|O_TRUNC, mode)

同名文件已经存在时，creat会截断然后打开文件

# Ex4.5

directory至少包含.、..2项，symlink的内容是路径名，至少有1个字符，所以它们的size都应该大于0

# Ex4.6

思路：

1. 文件长度保持一致，这个通过truncate/ftruncate来达成
2. 关于hole，每次读入1页大小，如果检查到全0，那么就lseek跳过；否则就写入

# Ex4.7

按题目描述，在创建core和创建core.copy间umask不变。创建core的程序可能不采用默认的umask，所以会导致这种情况

# Ex4.8

du只统计存在文件的大小

df会统计删除但仍然被进程占用的文件的大小

# Ex4.9

inode信息中有一项是指向该inode的hard link数。unlink会减少该计数，故而会修改inode信息，故而会改变file status modification time

# Ex4.10

假设一个opendir占用一个fd，那么打开fd数目的上限会限制ftw程序可探测的目录深度

# Ex4.11

修改后的程序见apue.3e/fieldir/ftw8-4.11.c。时间上差距不大

# Ex4.12

chroot指定一个目录为根目录，可以限制进程对于文件系统的访问在那个目录下

# Ex4.13

ex4.13/utimeone.c，思路是先通过lstat读取访问内容/修改内容时间，对于我们不想修改的部分直接用读到的内容填充。这样就实现了部分修改时间

# Ex4.14

不了解finger程序。时间的话，猜测是读取mail的stat信息然后计算

# Ex4.15

查看tar的archive格式，只存储了modification time。

查阅相关资料发现：在打包文件时需要读它的内容。所以archive里的文件的access time的一个合理值就是archive的创建时间