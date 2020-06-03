[TOC]

# Ex8.1

程序参见apue.3e/proc/vfork_simulate_fault.c

在我的系统上不会关闭stdout。通过用atexit注册关闭stdout的函数来模拟这个行为。



# Ex8.2

取决于child返回后是否修改了stack frame（例如，调用函数），修改了就会破坏parent目前的栈信息。

# Ex8.3

# Ex8.4

parent执行完毕后，child才会执行。

这样，child1就可能和parent2发生race condition。

为了解决这个问题，就要让parent和child都执行完后，才允许后面一个程序执行。在这里，让parent等child执行完可以达到目的

具体的同步，等之后学习到再来更新

# Ex8.5

经测试，输出的仍然是路径全称

（同样的interpreter文件，在linux下运行正常，而在mac上报bad interpreter。之后再看）

# Ex8.6

zombie：父进程未回收的已结束运行的子进程

从定义出发就可以得到程序