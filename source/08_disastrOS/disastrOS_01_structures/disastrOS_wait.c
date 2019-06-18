#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

void internal_wait(){
  int pid_to_wait=running->syscall_args[0];
  int* result=(int*) running->syscall_args[1];
  // error conditions:
  // the process has no children
  if (running->children.first == 0){
    running->syscall_retvalue = DSOS_EWAIT;
    return;
  }  
  //  we scan the list of pcbs
  // we stop either
  // - at the first process in zombie status, if pid==0;
  // - at the first process whose pid is the queried one
  PCB* awaited_pcb=0;
  PCBPtr* awaited_pcb_ptr=0;
  ListItem* aux=running->children.first;
  while(aux){
    awaited_pcb_ptr=(PCBPtr*) aux;
    awaited_pcb=awaited_pcb_ptr->pcb;
    if (pid_to_wait==0 && awaited_pcb->status==Zombie)
      break;
    if (pid_to_wait && awaited_pcb->pid==pid_to_wait)
      break;
    aux=aux->next;
  }

  // if we were looking for a process not in child list
  // we need to return an error
  if(pid_to_wait>0){
    if(! awaited_pcb){
      pid_to_wait = -1;
      running->syscall_retvalue = DSOS_EWAIT;
      return;
    } 
  }
  
  // if the pid is in zombie status, we return the value and free the memory
  if (awaited_pcb && awaited_pcb->status==Zombie) {
    // remove the awaited pcb from children list
    List_detach(&running->children, (ListItem*) awaited_pcb_ptr);
    PCBPtr_free(awaited_pcb_ptr);

    // remove he pc from zombie pool
    List_detach(&zombie_list, (ListItem*) awaited_pcb);
    running->syscall_retvalue = awaited_pcb->pid;
    if (result)
      *result = awaited_pcb->return_value;
    PCB_free(awaited_pcb);
    return;
  }

  // all fine, but the process is not a zombie
  // need to sleep
  running->status=Waiting;
  List_insert(&waiting_list, waiting_list.last, (ListItem*) running);

  // pick the next
  PCB* next_running= (PCB*) List_detach(&ready_list, ready_list.first);
  running=next_running;
}
