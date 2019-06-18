#include <stdlib.h>
#include <stdio.h>
#include "segment_item.h"
#include "process_memory_layout.h"
#include "string.h"

SegmentItem* SegmentItem_alloc() {
  return (SegmentItem*) malloc(sizeof(SegmentItem));
}

int SegmentItem_free(SegmentItem* item){
  free(item);
  return 0;
}

void SegmentItem_init(SegmentItem* item,
		      struct ProcessMemoryLayout* pmem,
		      uint32_t segment_id) {
  item->list.prev=item->list.next=0;
  item->pmem=pmem;
  item->segment_id=segment_id;
  List_init(&item->frame_list);
}

SegmentItem* SegmentList_byId(ListHead* list, uint32_t segment_id) {
  ListItem* aux=list->first;
  while(aux){
    SegmentItem* item=(SegmentItem*) aux;
    if (item->segment_id==segment_id)
      return item;
    aux=aux->next;
  }
  return 0;
}

void SegmentItem_print(SegmentItem* item){
  printf("  Segment {\n");
  printf("    segment_id: %d\n", item->segment_id);
  SegmentDescriptor* segment=item->pmem->segments+item->segment_id;
  printf("    base: %d", segment->base);
  printf("    limit: %d", segment->limit);
  printf("    pages: ");
  FrameList_print(&item->frame_list);
  printf("\n");
  printf("  }\n");
}

void SegmentList_print(ListHead* list) {
  ListItem* aux=list->first;
  while(aux){
    SegmentItem* item=(SegmentItem*) aux;
    SegmentItem_print(item);
    aux=aux->next;
    if(aux)
      printf(",");
    printf("\n");
  }
}
