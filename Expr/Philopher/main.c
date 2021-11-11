#include "mysemop.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
/* 全局变量 */
int room_sem_id = 0; /* 代表房间的信号量 */
int chopsticks_sem_id[5]; /* 代表筷子的信号量 */
int main() {
  /* 变量声明 */
  pid_t pid;
  pid_t chldpid[5];
  int i = 0;
  char ch;
  /* 初始化信号量 */
  room_sem_id = CreateSem(4); /* 房间可容纳下 4 个哲学家 */
  for (i = 0; i < 5; i++) { /* 5 根筷子，每根筷子同一时间只能被一人使用 */
    chopsticks_sem_id[i] = CreateSem(1);
  }
  /* 创建并初始化化子进程 */
  for (i = 0; i < 5; i++) {
    pid = fork();
    if (pid < 0) {
      fprintf(stderr,"When fork philosopher %d Failed!\n", i);
      exit(-1);
    }
    /* 子进程处理的代码 */
    if (pid == 0) {
      /* 哲学家吃饭演示核心 */
      while (1) {
        /* 哲学家正在思考 */
        printf("Philopher %d is thinking,No disterb!\n", i);
        sleep(1);
        /* 哲学家饿了，进入房间准备吃饭 */
        Psem(room_sem_id);
        printf("Philopher %d is hungry,so he entered the room.\n", i);
        /* 哲学家拿起左边的筷子 */
        Psem(chopsticks_sem_id[i]);
        printf("Philopher %d pick up left chopstick\n", i);
        /* 哲学家拿起右边的筷子 */
        Psem(chopsticks_sem_id[(i+1)%5]);
        printf("Philopher %d pick up right chopstick\n", i);
        /* 哲学家开始吃饭 */
        printf("Philopher %d begins to eat!\n", i);
        sleep(5 - i);
        /* 哲学家吃饭完毕 */
        printf("Philopher %d ends to eat!\n", i);
        /* 哲学家放下右边的筷子 */
        Vsem(chopsticks_sem_id[(i+1)%5]);
        printf("Philopher %d put down right chopstick\n", i);
        /* 哲学家放下左边的筷子 */
        Vsem(chopsticks_sem_id[i]);
        printf("Philopher %d put down left chopstick\n", i);
        /* 哲学家离开屋子继续思考 */
        Vsem(room_sem_id);
        printf("Philopher %d left the room!\n",i);
        printf("Philopher %d begins thinking!\n",i);
        sleep(1);
      }
    } else {
      chldpid[i] = pid;
    }
  }
  /* 主进程等待用户输入 */
  do {
    ch = getchar();
  } while (ch != 'q');
  /* 收到用户输入 q 以后中止所有子进程后退出 */
  for (i = 0; i < 5; i++) {
    kill(chldpid[i], SIGTERM);
    DeleteSem(chopsticks_sem_id[i]);
  }
  DeleteSem(room_sem_id);
}
