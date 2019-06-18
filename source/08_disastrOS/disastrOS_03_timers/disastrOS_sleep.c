#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

void internal_sleep(){
  //! determines how many cicles a process has to sleep, by reading the argument from
  //! the syscall
  if (running->timer) {
    printf("process has already a timer!!!\n");
    running->syscall_retvalue=DSOS_ESLEEP;
    return;
  }
  int cycles_to_sleep=running->syscall_args[0];
  int wake_time=disastrOS_time+cycles_to_sleep;
  
  TimerItem* new_timer=TimerList_add(&timer_list, wake_time, running);
  if (! new_timer) {
    printf("no new timer!!!\n");
    running->syscall_retvalue=DSOS_ESLEEP;
    return;
  } 
  running->status=Waiting;
  List_insert(&waiting_list, waiting_list.last, (ListItem*) running);
  if (ready_list.first)
    running=(PCB*) List_detach(&ready_list, ready_list.first);
  else {
    running=0;
    printf ("they are all sleeping\n");
    disastrOS_printStatus();
  }
}

