#pragma once
#include "frame_item.h"

struct ProcessMemoryLayout;

typedef struct SegmentItem{
  ListItem list;
  struct ProcessMemoryLayout* pmem;
  int segment_id; // id of the segment in the segment descriptors
  ListHead frame_list;
} SegmentItem;

SegmentItem* SegmentItem_alloc();

int SegmentItem_free(SegmentItem* item);

SegmentItem* SegmentList_byId(ListHead* list, uint32_t segment_id);

void SegmentItem_init(SegmentItem* item,
		      struct ProcessMemoryLayout* pmem,
		      uint32_t segment_id);

void SegmentItem_print(SegmentItem* item);

void SegmentList_print(ListHead* list);
