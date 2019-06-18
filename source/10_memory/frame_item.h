#pragma once
#include <assert.h>
#include <stdio.h>
#include "fake_mmu.h"
#include "linked_list.h"

//this is a record of the pages list. It holds the page number and the pid for a process
typedef struct FrameItem{
  ListItem list;
  int pid;
  uint32_t frame_num;
} FrameItem;


FrameItem* FrameItem_alloc();
int FrameItem_free(FrameItem* item);
void FrameItem_init(FrameItem* item, int pid, uint32_t frame_num);
void FrameItem_print(FrameItem* item);
void FrameList_print(ListHead* list);
