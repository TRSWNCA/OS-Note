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

  

