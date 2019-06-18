#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

// replaces the running process with the next one in the ready list
void internal_schedule() {
  if (running) {
    disastrOS_debug("PREEMPT - %d ->", running->pid);
   }
  // at least one process should be in the running queue
  // if not, no preemption occurs
  
  if (ready_list.first){
    PCB* next_process=(PCB*) List_detach(&ready_list, ready_list.first);
    running->status=Ready;
    List_insert(&ready_list, ready_list.last, (ListItem*) running);
    next_process->status=Running;
    running=next_process;
  }
  //disastrOS_printStatus();
 
  if (running) {
    disastrOS_debug(" %d\n", running->pid);
  }
}
