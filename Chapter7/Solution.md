[TOC]

# Ex7.1

eax中存放的是printf的返回值，也就是输出字符的计数，13。



# Ex7.2

- 指向终端的stdout默认是line buffered的，所以调用printf后会立即输出
- atexit相当于向一个“exit handler栈”中压入函数，最后调用相当于pop，反序。

# Ex7.3

（trick）无优化的x86_64，main的stack frame会在rbp基础上复制一份通过寄存器传入的参数

```assembly
__text:0000000100000F38 mov     [rbp+var_4], 0
__text:0000000100000F3F mov     [rbp+var_8], edi
__text:0000000100000F42 mov     [rbp+var_10], rsi
```

利用此特性，内嵌汇编，通过rbp往回去找参数



# Ex7.4

用来捕获对于空指针的dereference

# Ex7.5

```c
typedef void Exitfunc(void);
int atexit(Exitfunc*);
```

# Ex7.6

calloc会清0分配的内存

# Ex7.7

heap和stack是runtime分配的，大小不定。

# Ex7.8

可执行文件还有其他segment和一个header

#Ex7.9

根据我对linker的了解，指定static编译会将archive中包含被程序引用函数的整个object文件包含进最终的可执行文件中（当然定位需要修正）

# Ex7.10

正确。并未返回对于已释放stack frame的引用