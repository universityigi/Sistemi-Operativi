#include <stdlib.h>
#include <stdio.h>
#include "segment_item.h"
#include "process_memory_layout.h"
#include "string.h"

ProcessMemoryLayout* ProcessMemoryLayout_alloc(){
  return (ProcessMemoryLayout*) malloc(sizeof(ProcessMemoryLayout));
}

ProcessMemoryLayout* ProcessMemoryList_byPid(ListHead* head, int pid){
  ListItem* aux=head->first;
  while(aux){
    ProcessMemoryLayout* item=(ProcessMemoryLayout*)aux;
    if(item->pid==pid)
      return item;
    aux=aux->next;
  }
  return 0;
}
int ProcessMemoryLayout_free(ProcessMemoryLayout* pmem){
  free(pmem);
  return 0;
}

void ProcessMemoryLayout_init(ProcessMemoryLayout* pmem, int pid) {
  pmem->list.prev=pmem->list.next=0;
  pmem->pid=pid;
  memset(pmem->pages, 0, sizeof(PageEntry)*PAGES_NUM);
  List_init(&pmem->segments_list);
  
  // we fill the segment map with invalid bits
  for (int s=0; s<SEGMENTS_NUM; ++s){
    SegmentDescriptor* des=pmem->segments+s;
    des->base=0;
    des->limit=0;
    des->flags &= ~Valid;
  }
  for (int p=0; p<PAGES_NUM; ++p){
    pmem->pages[p].flags&=(~Valid);
    pmem->pages[p].frame_number=p;
  }
  
};

void ProcessMemoryLayout_print(ProcessMemoryLayout* pmem) {
  printf("ProcessMemory {\n");
  printf("  pid: %d\n", pmem->pid);
  printf("  num_segments: %d", pmem->segments_list.size);
  printf("  segments: {\n");
  SegmentList_print(&pmem->segments_list);
  printf("  }\n");
  printf("}\n");
}


