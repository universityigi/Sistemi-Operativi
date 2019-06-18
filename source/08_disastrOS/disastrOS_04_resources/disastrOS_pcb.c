#include <assert.h>
#include <stdio.h>

#include "pool_allocator.h"
#include "disastrOS_pcb.h"
#include "disastrOS.h"
#include "disastrOS_globals.h"
#include "disastrOS_timer.h"

#define PCB_SIZE sizeof(PCB)
#define PCB_MEMSIZE (sizeof(PCB)+sizeof(int))
#define PCB_BUFFER_SIZE MAX_NUM_PROCESSES*PCB_MEMSIZE

static char _pcb_buffer[PCB_BUFFER_SIZE];
static PoolAllocator _pcb_allocator;

#define PCBPTR_SIZE sizeof(PCBPtr)
#define PCBPTR_MEMSIZE (sizeof(PCBPtr)+sizeof(int))
#define PCBPTR_BUFFER_SIZE MAX_NUM_PROCESSES*PCBPTR_MEMSIZE

static char _pcb_ptr_buffer[PCBPTR_BUFFER_SIZE];
static PoolAllocator _pcb_ptr_allocator;



void PCB_init(){
    int result=PoolAllocator_init(& _pcb_allocator,
				  PCB_SIZE,
				  MAX_NUM_PROCESSES,
				  _pcb_buffer,
				  PCB_BUFFER_SIZE);
    assert(! result);

    result=PoolAllocator_init(& _pcb_ptr_allocator,
			      PCBPTR_SIZE,
			      MAX_NUM_PROCESSES,
			      _pcb_ptr_buffer,
			      PCBPTR_BUFFER_SIZE);
    assert(! result);
}

PCB* PCB_alloc() {
  PCB* pcb = (PCB*) PoolAllocator_getBlock(&_pcb_allocator);
  pcb->list.prev=0;
  pcb->list.next=0;
  pcb->pid=last_pid; last_pid++;
  pcb->return_value=0;
  pcb->status=Invalid;
  pcb->last_fd=0;
  pcb->signals=0;
  pcb->signals_mask=0xFFFFFFFF;
  pcb->status=Invalid;
  List_init(&pcb->descriptors);
  pcb->parent=0;
  pcb->timer=0;
  List_init(&pcb->children);
  return pcb;
}

int PCB_free(PCB* pcb){
  return PoolAllocator_releaseBlock(&_pcb_allocator, pcb);
}

PCBPtr* PCBPtr_alloc(PCB* pcb) {
  PCBPtr* pcb_ptr=(PCBPtr*) PoolAllocator_getBlock(&_pcb_ptr_allocator);
  pcb_ptr->list.prev=0;
  pcb_ptr->list.next=0;
  pcb_ptr->pcb=pcb;
  return pcb_ptr;
}

int PCBPtr_free(PCBPtr* pcb_ptr){
  return PoolAllocator_releaseBlock(&_pcb_ptr_allocator, pcb_ptr);
}

PCB* PCB_byPID(ListHead* head, int pid){
  ListItem* aux=head->first;
  while (aux) {
    PCB* pcb=(PCB*) aux;
    if (pcb->pid==pid)
      return pcb;
    aux=aux->next;
  }
  return 0;
}

PCBPtr* PCBPtr_byPID(ListHead* head, int pid){
  ListItem* aux=head->first;
  while (aux) {
    PCBPtr* pcb_ptr=(PCBPtr*) aux;
    if (pcb_ptr->pcb->pid==pid)
      return pcb_ptr;
    aux=aux->next;
  }
  return 0;
}



/* DEBUG FUNCTIONS */

void PCBPtrList_print(ListHead* head) {
  ListItem* aux=head->first;
  printf("(");
  while(aux){
    PCBPtr* pcb_ptr= (PCBPtr*) aux;
    printf("%d", pcb_ptr->pcb->pid);
    aux=aux->next;
    if (aux)
      printf(", ");
  }
  printf(")");
}

void PCB_print(PCB* pcb){
  printf("[pid: %d, child: ", pcb->pid);
  
  PCBPtrList_print(&pcb->children);
  printf("]");
}

void PCBList_print(ListHead* head) {
  ListItem* aux=head->first;
  printf("{\n");
  while(aux){
    printf("\t");
    PCB* pcb= (PCB*) aux;
    PCB_print(pcb);
    aux=aux->next;
    if (aux)
      printf(",");
    printf("\n");
  }
  printf("}\n");
}

