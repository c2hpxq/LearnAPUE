[TOC]

# Ex5.2

line-buffered，意味着

- 遇到换行符
- 缓冲区满

就会进行IO。

# Ex5.3

没有输出字符，例如printf("");

# Ex5.4

getchar返回值为int，putchar接收的输入也为int。

例如EOF截断成char的值和原值不相等

# Ex5.5

如果要将目前写入文件的内容全部同步到对应的设备上，那么就要

1. 先fflush，将滞留在buffer中的内容刷到kernel提供给IO的缓存中，这样IO缓存中的内容就是当前最新的文件内容了；
2. 再fsync，将IO缓存中的内容更新到磁盘/设备上。这样，就保证了磁盘/设备上的内容是最新的了。

如果不fflush，直接fsync，在“语义”上也不会有错误，只是此时磁盘上的内容可能落后于目前在操作的文件最新状态。

# Ex5.6

猜测可能fgets会强制刷buffer

对stdin的操作“影响”到stdout。。。存疑

# Ex5.7

暂不考虑对于权限的解析，只提供可读可写。

提供给myfmemopen的缓冲区将由其管理，在close时会free，大小不足时会realloc。