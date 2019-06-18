#pragma once
#include <ucontext.h> // this is the cpu status
#include "disastrOS_constants.h"
#include "linked_list.h"
#include "disastrOS_timer.h"

typedef enum ProcessStatus {Invalid=-1,
			    Created=0x0,
			    Running=0x1,
			    Ready=0x2,
			    Waiting=0x3,   // io or semaphore wait
			    Suspended=0x4, // ctrl-z
			    Zombie=0x5}
  ProcessStatus;
		    
typedef struct PCB{
  ListItem list;  // MUST BE THE FIRST!!!
  int pid;
  int return_value; // ret value for the parent
  ProcessStatus status;
  int signals;
  int signals_mask;
  struct PCB* parent;
  ListHead children;
  ucontext_t cpu_state;
  // timers
  struct TimerItem *timer;

  // descriptors (for all resources)
  int last_fd;
  ListHead descriptors;
  
  
  //we are really rude :) the stack is INSIDE the pcb
  //forgive me for the bestiality
  char stack[STACK_SIZE];

  // more stuff to come

  
  //the one below is a hack for the syscalls
  //in a real system one needs to use the cpu to pass
  //arguments to a syscall

  // we use long int so we can store pointers on 64 bit machines
  int syscall_num;
  long int syscall_args[DSOS_MAX_SYSCALLS_ARGS]; 
  int syscall_retvalue;
} PCB;

// initializes the memory allocation
// for the PCB structures
// called internally
void PCB_init();

// allocates and initializes a new pcb block
PCB* PCB_alloc();

// frees a pcb block
int PCB_free(PCB* pcb);

// prints a PCB
void PCB_print(PCB* pcb);

// returns a pcb whose pid is pid in the list
PCB* PCB_byPID(ListHead* head, int pid);

// prints a list of PCB
void PCBList_print(ListHead* head);

// this is a list of *pointers* to pcb used in many cases
typedef struct PCBPtr{
  ListItem list;
  PCB* pcb;
} PCBPtr;

// allocates a list item whose data field
// is a pointer to a PCB
PCBPtr* PCBPtr_alloc(PCB* pcb);

// frees a PCB item
int PCBPtr_free(PCBPtr* pcb);

// returns a pcb whose pid is pid in the list of pointers
PCBPtr* PCBPtr_byPID(ListHead* head, int pid);

// prints a list of pcb ptrs
void PCBPtrList_print(ListHead* head);


