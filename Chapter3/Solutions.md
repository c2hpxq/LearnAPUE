[TOC]

# Ex3.1

参考3.9节I/O Efficiency中关于read-ahead的讨论和Figure 3.6的实验结果。

被测操作系统（Linux）检测到超过一定长度的连续I/O读，采取“接下来的内容很可能在近期被读到”的启发操作，进而预读取。读取32个字节以上，没有到磁盘传输单位，所花的总时间已经近乎最优，证明了这一点。

# Ex3.2

测试程序见dup2.c

题目限制不允许使用fcntl函数。目前解决“跳过”大片fd的思路是：不断dup，直到得到我们想要的fd2，再将先前“占位”的结果全都close掉。

测试结果：

```
read 8 form fd = 3
#include

detect #max-file-descriptor: 12800
Creating placeholder ...
4 5 6 7 8 9 17 18 19 20 
Closing placeholder ...
19 18 17 9 8 7 6 5 4 
succ dup2 3 to 20
read 8 form fd = 20
 <unistd
```

从中可以看到

- sysconf探测到系统fd范围为[0, 12799]
- dup出来的fd指向file table中同一个entry，故而有相同的current file offset。所以从fd=20会从fd=3上次读剩下的内容开始继续读。

为了验证fd的上限，编写一个测试程序test-max-fd.c：一直open直到遇到错误。测试结果：

```
error encountered: : Too many open files
max fd = 12799
```

验证了从系统中获取的上限。

再查看dup2at12800.c的结果：

> error encountered: : Bad file descriptor
> -1

可以进一步验证范围为[0,12799]。

# Ex3.3

fcntl改变已经打开的文件的属性

F_SETFD修改每个fd的status

F_SETFL修改file table entry的status，dup出来的fd和原fd指向的是同一个fte

# Ex3.4

dup2在fd=fd2时直接返回。如果fd=0,1,2，会将dup2的结果close

# Ex3.5

```shell
./a.out > outfile 2&>1
```

shell先将1（stdout）重定向到outfile，然后将2（stderr）重定向到1。

```shell
./a.out 2>&1 > outfile
```

2先和1都指向terminal，然后把1重定向到outfile。