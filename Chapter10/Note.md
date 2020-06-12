#信号

## 信号的基本概念

- 软件中断机制，提供处理异步事件的机制。
  - e.g.，让程序处理ctrl+c

- 每个信号都有一个名称，以SIG开头。其值均为正整数，定义在signal.h中
  - kill函数用于发送信号，0有特殊用途
- 使用kill向某个process发送信号的要求
  - process owner
  - superuser

- 软硬件都能导致信号产生
  - 硬件，如SIGFPE、SIGSEGV
  - 软件，如SIGPIPE（写入一个没有reader的pipe）、SIGALRM（进程自己设定的alarm超时）

### 应对信号的action

1. ignore。除了SIGKILL、SIGSTOP不可忽略外，其余均允许忽略
2. catch the signal，执行我们自定义的行为。类似地，SIGKILL、SIGSTOP的行为（结束、挂起进程）不可修改
3. 采取默认行为

##  注册信号处理函数

API：signal

action

1. SIG_IGN，忽略
2. 提供自定义的函数
3. SIG_DFL，默认行为

返回值要么是

1. 旧的action
2. 出错，SIG_ERR

### exec

- 清除所有自定义，设为DFL（地址空间整体替换了，没有意义了）
- 保持DFL和IGN（不是全改为DFL，忽略的仍然忽略）。

### fork

子进程继承父进程的信号处理方式



## 打断系统调用

### slow syscall

- 读、写、打开terminal、network之类未必马上就绪的“文件”
- pause，就是用来打断的
- 一些ioctl
- 一些IPC

当进程正在slow syscall中，收到信号，处理信号会打断syscall。之后

- 打断并返回EINTR，让用户自己决定要不要restart
- 自动restart

这些行为在一些系统上可以配置



## 可重入函数

可能出错的例子：

- malloc。如果signal handler中有malloc且和程序正常执行流中的malloc形成race condition，那么潜在内部结构，如linkedlist等会被破坏

所以不是任何函数都可以在信号处理中调用的，必须保证“async signal safe“

常见的一些不安全因素

- 使用了static变量。
- 调用了malloc、free之类

- 使用了全局变量，例如stdio中的一些函数
- 注意errno。一般一个thread有一份errno，潜在会有race condition。
  - 一般需要在sighandler中保存+恢复errno

（所以要原子地修改全局数据结构之类，阻断一切并发，不仅要加锁，还需要屏蔽signal）

（现在估计getpwnam中有锁之类的机制，在我的pc上程序stuck了）



## SIGCLD、SIGCHLD

暂略

## kill、raise

kill给pid发signo

raise给自己发signo



#### 对于kill的pid

- pid>0，给指定pid的进程发
- pid=0，给和自己process group id相同的，且自己有权限发的进程发
- pid<0，process group id=|pid|且有权限
- pid=-1，给所有有权限的发

#### 这里的权限

- superuser可以给任意进程发送
- 其他用户rid、eid相等
- 特例：同一个session中可以互相发SIGCONT

#### null signo

signo=0，kill不会给进程发信号，但是仍会进行错误检查（如进程已经不存在了，或说更准确一些，指定pid的进程不存在）



## alarm

setjmp+longjmp可能会中止执行到中途的其他信号处理函数

常用计时pattern。（虽然并未避免上述问题）

```c
setjmp
alarm(10)
read
alarm(0)

...
  
void alarm_handler(int ) {
  longjmp
}
```



## Signal set

sigset_t

集合操作

sigemptyset，清空

sigfillset，包含所有信号

sigaddset，添加一个信号

sigdelset，删除一个信号

sigismember，成员判断



## sigprocmask

- 设置进程屏蔽哪些信号

- how：SIG_BLOCK、SIG_UNBLOCK、SIG_SETMASK

- 如果完毕后，若kernel发现有unblocked signal，那么会在返回前把它deliver给进程
- 仅针对单线程

## sigpending

查看哪些信号目前被block待处理

## sigaction

- sa_mask可以指定在处理该信号前，要将哪些信号block了。在处理完后恢复原先的mask

- OS保证我们目前正在处理的signal一定被block

- sa_flags 可以指定是否中断、自动restart之类

- 信息更完善的sig handler：

  ```c
  void (*sa_sigaction)(int, siginfo_t *, void * context)
  ```

  siginfo_t中：

  - si_code可以额外指明信号附加信息，如SIGILL，ILL_ILLOPC非法opcode、ILL_ILLOPN非法操作数等
  - si_addr可以在SIG_SEGV、SIG_ILL等的处理时提供触发的地址

# sigsetjmp、siglongjmp

信号处理函数会屏蔽当前正在处理的信号，在signal handler中longjmp的话，如何恢复mask这一行为在不同系统中的实现不统一

sigsetjmp提供savemask参数，非0则表示在env中存入mask，之后对应的siglongjmp会恢复到当时存入的mask



## sigsuspend

目的：unblock某个（些）信号并**立刻**等待对应的信号deliever过来。

sigprocmask+pause并不能保证这一点

- sigprocmask前信号block在那里，那么之后信号在pause之前就处理了。然后pause死等；
- 不要pause显然不对：如果信号没有block，那么sigprocmask执行后将会立即继续执行接下来的代码。

完成这个动作需要**原子操作**：切换并sleep等待。sigsuspend就是起这个作用的。设置完mask后就等待，直到一个sig handler执行并返回，它才返回。