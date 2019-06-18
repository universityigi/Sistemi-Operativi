#include <stdlib.h>
#include <stdio.h>
#include "frame_item.h"

FrameItem* FrameItem_alloc() {
  return (FrameItem*) malloc (sizeof(FrameItem));
}

int FrameItem_free(FrameItem* item) {
  free(item);
  return 0;
}

void FrameItem_init(FrameItem* item, int pid, uint32_t frame_num){
  item->list.prev=item->list.next=0;
  item->pid=pid;
  item->frame_num=frame_num;
}

void FrameItem_print(FrameItem* item){
  printf("(pid: %d, frame: %d)", item->pid, item->frame_num);
}

void FrameList_print(ListHead* list) {
  ListItem* aux=(ListItem*) list->first;
  while(aux){
    FrameItem_print((FrameItem*) aux);
    aux=aux->next;
    if(aux)
      printf(", ");
  }
  
}
