#include <sys/types.h>
#include <sys/time.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

FILE* log_file=NULL;
PCB* init_pcb;
PCB* running;
int last_pid;
ListHead ready_list;
ListHead waiting_list;
ListHead zombie_list;
ListHead timer_list;

// a resource can be a device, a file or an ipc thing
ListHead resources_list;

SyscallFunctionType syscall_vector[DSOS_MAX_SYSCALLS];
int syscall_numarg[DSOS_MAX_SYSCALLS];

int shutdown_now=0; // used for termination
volatile int disastrOS_time=0;

void disastrOS_trap(){
  int syscall_num=running->syscall_num;
  if (log_file)
    fprintf(log_file, "TIME: %d\tPID: %d\tACTION: %s %d\n",
	    disastrOS_time,
	    running->pid,
	    "SYSCALL_IN",
	    syscall_num);
  
  if (syscall_num<0||syscall_num>DSOS_MAX_SYSCALLS) {
    running->syscall_retvalue = DSOS_ESYSCALL_OUT_OF_RANGE;
    goto return_to_process;
  }
  SyscallFunctionType my_syscall=syscall_vector[syscall_num];
  if (! my_syscall) {
    running->syscall_retvalue = DSOS_ESYSCALL_NOT_IMPLEMENTED;
    goto return_to_process;
  }
 
  disastrOS_debug("syscall: %d, pid: %d\n", syscall_num, running->pid);
  (*syscall_vector[syscall_num])();
  //internal_schedule();
 return_to_process:
  if (log_file)
    fprintf(log_file, "TIME: %d\tPID: %d\tACTION: %s %d\n",
	    disastrOS_time,
	    running->pid,
	    "SYSCALL_OUT",
	    syscall_num);
  if (!running) {
    printf("no active processes\n");
    disastrOS_printStatus();
  }
}

int disastrOS_syscall(int syscall_num, ...) {
  assert(running); 
  va_list ap;
  if (syscall_num<0||syscall_num>DSOS_MAX_SYSCALLS)
    return DSOS_ESYSCALL_OUT_OF_RANGE;

  int nargs=syscall_numarg[syscall_num];
  va_start(ap,syscall_num);
  for (int i=0; i<nargs; ++i){
    running->syscall_args[i] = va_arg(ap,long int);
  }
  va_end(ap);
  running->syscall_num=syscall_num;
  disastrOS_trap();
  return running->syscall_retvalue;
}


void disastrOS_start(void (*f)(void*), void* f_args, char* logfile){  
  /* INITIALIZATION OF SYSTEM STRUCTURES*/
  disastrOS_debug("initializing system structures\n");
  PCB_init();
  init_pcb=0;

  // populate the vector of syscalls and number of arguments for each syscall
  for (int i=0; i<DSOS_MAX_SYSCALLS; ++i){
    syscall_vector[i]=0;
  }
  syscall_vector[DSOS_CALL_PREEMPT]   = internal_preempt;
  syscall_numarg[DSOS_CALL_PREEMPT]   = 0;
  
  syscall_vector[DSOS_CALL_FORK]      = internal_fork;
  syscall_numarg[DSOS_CALL_FORK]      = 0;

  syscall_vector[DSOS_CALL_SPAWN]      = internal_spawn;
  syscall_numarg[DSOS_CALL_SPAWN]      = 2;

  syscall_vector[DSOS_CALL_WAIT]      = internal_wait;
  syscall_numarg[DSOS_CALL_WAIT]      = 2;

  syscall_vector[DSOS_CALL_EXIT]      = internal_exit;
  syscall_numarg[DSOS_CALL_EXIT]      = 1;

  syscall_vector[DSOS_CALL_SHUTDOWN]      = internal_shutdown;
  syscall_numarg[DSOS_CALL_SHUTDOWN]      = 0;

  // setup the scheduling lists
  running=0;
  List_init(&ready_list);
  List_init(&waiting_list);
  List_init(&zombie_list);
  List_init(&resources_list);
  List_init(&timer_list);


  /* INITIALIZATION OF SYSCALL AND INTERRUPT INFRASTRUCTIRE*/
  running=PCB_alloc();
  running->status=Running;
  init_pcb=running;
  
  // we start the first process
  disastrOS_debug("starting\n");
  (*f)(f_args);
}

int disastrOS_fork(){
  return disastrOS_syscall(DSOS_CALL_FORK);
}

int disastrOS_wait(int pid, int *retval){
  return disastrOS_syscall(DSOS_CALL_WAIT, pid, retval);
}

void disastrOS_exit(int exitval) {
  disastrOS_syscall(DSOS_CALL_EXIT, exitval);
}

void disastrOS_preempt() {
  disastrOS_syscall(DSOS_CALL_PREEMPT);
}

void disastrOS_spawn(void (*f)(void*), void* args ) {
  disastrOS_syscall(DSOS_CALL_SPAWN, f, args);
}

void disastrOS_shutdown() {
  disastrOS_syscall(DSOS_CALL_SHUTDOWN);
}

int disastrOS_getpid(){
  if (! running)
    return -1;
  return running->pid;
}

void disastrOS_printStatus(){
  printf("****************** DisastrOS ******************\n");
  printf("Running: ");
  if (running)
    PCB_print(running);
  printf("\n");
  printf("\nReady: ");
  PCBList_print(&ready_list);
  printf("\nWaiting: ");
  PCBList_print(&waiting_list);
  printf("\nZombie: ");
  PCBList_print(&zombie_list);
  printf("\n***********************************************\n\n");
};
