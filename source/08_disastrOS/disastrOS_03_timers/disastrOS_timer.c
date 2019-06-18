#include <assert.h>
#include <stdio.h>
#include "disastrOS_timer.h"
#include "pool_allocator.h"
#include "disastrOS_pcb.h"

#define TIMER_ITEM_SIZE sizeof(TimerItem)
#define TIMER_ITEM_MEMSIZE (sizeof(TimerItem)+sizeof(int))
#define TIMER_ITEM_BUFFER_SIZE MAX_NUM_PROCESSES*TIMER_ITEM_MEMSIZE

static char _timer_item_buffer[TIMER_ITEM_BUFFER_SIZE];
static PoolAllocator _timer_item_allocator;

void Timer_init(){
  int result=PoolAllocator_init(& _timer_item_allocator,
				TIMER_ITEM_SIZE,
				MAX_NUM_PROCESSES,
				_timer_item_buffer,
				TIMER_ITEM_BUFFER_SIZE);
  assert(! result);
}

TimerItem* TimerItem_alloc(int awakening_time, PCB* pcb){
  TimerItem* item=(TimerItem*) PoolAllocator_getBlock(&_timer_item_allocator);
  if (! item)
    return 0;
  item->list.prev=0;
  item->list.next=0;
  item->pcb=pcb;
  item->awakening_time=awakening_time;
  return item;
}

int TimerItem_free(TimerItem* item){
  return PoolAllocator_releaseBlock(&_timer_item_allocator, (void*) item);
}

void TimerList_init(ListHead* timers) {
  List_init(timers);
}

typedef ListHead TimerHandler;

TimerItem* TimerList_add(ListHead* timers, int awakening_time, PCB* pcb){
  // scans the list until the next element has an awakening time larger than the current
  ListItem* aux=timers->first;
  TimerItem* item=(TimerItem*) aux;
  TimerItem* previous_item=0;
  while(aux){
    item=(TimerItem*) aux;
    if (awakening_time < item->awakening_time)
      break;
    previous_item=item;
    aux=aux->next;
  }
  TimerItem* new_item=TimerItem_alloc(awakening_time, pcb);
  if (! new_item)
    return 0;
  List_insert(timers, (ListItem*) previous_item, (ListItem*)new_item);
  return new_item;
}

TimerItem* TimerList_current(ListHead* timers, int current_time){
  if (! timers->first)
    return 0;
  TimerItem* item = (TimerItem*) timers->first;
  if (current_time>=item->awakening_time)
    return item;
  return 0;
}

int TimerList_removeCurrent(ListHead* timers){
  TimerItem* item = (TimerItem*) List_detach(timers, timers->first);
  if (! item)
    return -1;
  TimerItem_free(item);
  return 0;
}

void TimerList_print(ListHead* timers) {
  printf("[");
  TimerItem* aux=(TimerItem*) timers->first;
  while(aux){
    printf("(pid:%d, t:%d)", aux->pcb->pid, aux->awakening_time);
    aux=(TimerItem*) aux->list.next;
    if (aux)
      printf(", ");
  }
  printf("]");
}
