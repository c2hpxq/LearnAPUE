[TOC]

# Ex4.1

stat会follow symbolic link，所以查看的总是最终指向的文件的状态。也因此，st_mode应永不会为symlink

ex4.1程序查看当前目录下的普通文件file和指向file的symlink，查询到的都是regular file类型

```shell
$ ./a.out file symlink
file: regular
symlink: regular
```

