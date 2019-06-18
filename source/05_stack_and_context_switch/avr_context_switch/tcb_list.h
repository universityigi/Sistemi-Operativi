#pragma once
#include "tcb.h"

// simple double linked list of TCBs
typedef struct {
  struct TCB* first;
  struct TCB* last;
  uint8_t size;
} TCBList;

// global list of tcbs containing the running processes
extern TCBList tcb_queue;

// removes (if any) first tcb from the list
TCB* TCBList_dequeue(TCBList* list);

// adds new detached tcb to the list
uint8_t TCBList_enqueue(TCBList* list, TCB* tcb);

// for debug only
void TCBList_print(TCBList* list);
