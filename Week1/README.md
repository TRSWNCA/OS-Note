# Week1

## Reading

### Concepts

- process: a running program, including:

  - instructions: implement the program
  - data: variables
  - stack: organize program's procedure calls

  process invoke *system call* , making kernel performs a service and return (**kernel space**), and normal workload (**user space**)

- privilege:

  - kernel ensure: hardware protection mechanisms by **CPU**
  - user: don't care, only raise system call

- shell:

  - **user program** that reads commands from the user and executes them



### Notes for xv6

- xv6-process:

  - consists of **user-space memory** (instructions, data, and stack) and **per-process
    state private** to the kernel
  - xv6 **time-shares** processes
  - kernel associates a process identifier(*PID*) with each process
- fork()

  - create process with same data and instructions
  - is the *child* of the caller process, which called *parent*
  - parent's fork() return child's PID, and child's fork() return 0, which identifies the privilege
- file descriptor

  - uses as an index into a per-process table, so that every process has a private space of file descriptors starting at zero
  - 0 standard input, 1 standard output, 2 standard error
  - shell ensures at least 3 file descriptors
- pipe

  - a small kernel buffer exposed to processes as a pair of the file descriptors (in, out)
- file system
  - contain uninterpreted byte arrays, and directories
  - metadata of inode 

### Notes for real world

- Standard
  - base on POSIX
  - system call interface
  - more kernel services
  - offer many features beyond POSIX
- Multics design 
- Multi-users

## Lab

My PC just fits the condition:

```
Linux LAPTOP-5DSBBEQG 5.4.72-microsoft-standard-WSL2 #1 SMP Wed Oct 28 23:40:43 UTC 2020 x86_64 x86_64 x86_64 GNU/Linux
```

### Boot xv6

```bash
$ git clone git://g.csail.mit.edu/xv6-labs-2021 && cd xv6-labs-2021 && git checkout util
```

Before make the project, we need to configure some environments:

```bash
$ sudo apt install autoconf automake libtool libffi-dev
```

And also

```bash
$ sudo apt install build-essential gdb-multiarch qemu-system-misc gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu 
```

Do make:

```
$ make qemu
riscv64-linux-gnu-gcc -Wall -Werror -O -fno-omit-frame-pointer -ggdb -DSOL_UTIL -DLAB_UTIL -MD -mcmodel=medany -ffreestanding -fno-common -nostdlib -mno-relax -I. -fno-stack-protector -fno-pie -no-pie  -c -o kernel/kalloc.o kernel/kalloc.c
riscv64-linux-gnu-gcc: error: unrecognized command line option ‘-mno-relax’; did you mean ‘-Wno-vla’?
Makefile:135: recipe for target 'kernel/kalloc.o' failed
make: *** [kernel/kalloc.o] Error 1
```

The problem is that the compiler doesn't support the option. I use `gcc-8` instead.

```
$ sudo apt install gcc-8-riscv64-linux-gnu
$ sudo update-alternatives --install /usr/bin/riscv64-linux-gnu-gcc riscv64-linux-gnu-gcc /usr/bin/riscv64-linux-gnu-gcc-8 1
```

Moreover my qemu not installed:

```bash
$ sudo apt install libsdl1.2-dev
$ sudo apt install libtool-bin
$ sudo apt install libglib2.0-dev
$ sudo apt install libz-dev
$ sudo apt install libpixman-1-dev
$ git clone https://github.com/mit-pdos/6.828-qemu --depth=1 ~/qemu && cd ~/qemu
$ ./configure --disable-kvm --disable-werror --target-list="i386-softmmu x86_64-softmmu"
```

And then

  

