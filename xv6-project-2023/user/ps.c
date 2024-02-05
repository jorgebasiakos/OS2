#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"
#include "kernel/syscall.h"
#include "kernel/memlayout.h"
#include "kernel/riscv.h"
#include "kernel/spinlock.h"
#include "kernel/proc.h"



int main(void) {
  struct pstat pstatt;
  const char* states[] = {"UNUSED", "USED", "SLEEPNG", "RUNBL", "RUNNG", "ZOMBIE"};

  setpriority(4);

  if (getpinfo(&pstatt) == 0) {
    printf("Name\tPID\tPrio.\tState\tSize\n");
    for (int i = 0; i < NPROC; i++) {
      if(pstatt.inuse[i] == 1){
        printf("%s\t%d\t%d\t%s\t%d\n",
          pstatt.name[i], pstatt.pid[i], 
          pstatt.priority[i], states[pstatt.state[i]],
          pstatt.sz[i]);
      }
    }

  } 
  else {
    printf("Error in getpinfo\n");
    return -1;
  }
  return 0;
}
