#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
// returns 0 if successful, and -1 otherwise
int sys_set_limit(void) {
    int cpu_quota, memory_quota;
    if (argint(0, &cpu_quota) < 0 || argint(1, &memory_quota) < 0)
        return -1;

    struct proc *p = myproc();
    p->memory_quota = memory_quota;  // store the memory quota
    return 0;
}

// returns 0 if successful, and -1 otherwise
int sys_increase_memory_usage(void) {
    int amount;
    if (argint(0, &amount) == 0)
        return -1;

    struct proc *p = myproc();
    if (p->memory_usage + amount > p->memory_quota) // check against quota
        return -1;

    p->memory_usage += amount;
    // p->memory_usage = (p->memory_usage >= 0) ? p->memory_usage : 0;
    return 0;
}
