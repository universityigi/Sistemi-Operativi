#pragma once
#include "frame_item.h"
#include "segment_item.h"

typedef struct ProcessMemoryLayout {
  ListItem list;
  int pid;

  SegmentDescriptor segments[SEGMENTS_NUM];
  
  PageEntry pages[PAGES_NUM];
  ListHead segments_list;

} ProcessMemoryLayout;

ProcessMemoryLayout* ProcessMemoryLayout_alloc();
ProcessMemoryLayout* ProcessMemoryList_byPid(ListHead* head, int pid);

int ProcessMemoryLayout_free(ProcessMemoryLayout* pmem);
void ProcessMemoryLayout_init(ProcessMemoryLayout* pmem, int pid);
void ProcessMemoryLayout_print(ProcessMemoryLayout* pmem);
