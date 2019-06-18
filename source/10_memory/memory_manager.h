#pragma once
#include <assert.h>
#include <stdio.h>
#include "process_memory_layout.h"
#include "linked_list.h"

typedef struct GlobalMemoryLayout{
  int frame_to_pid[PAGES_NUM];
  ListHead frame_list;
  ListHead process_list;
} GlobalMemoryLayout;

/**
   initializes the global memory layout
   // the free pages list contains all memory
   // the process list contains no processes
*/
void Memory_init();


/**
   frees initializes the global memory layout
*/
void Memory_shutdown();

/**
   retrieves if existing the process layout of pid
*/
ProcessMemoryLayout* Memory_byPid(int pid);

/**
   adds a process with pid to the list. The process has no memory allocated and no segments
 */
ProcessMemoryLayout* Memory_addProcessLayout(int pid);

/**
   returns, if present a segment having segment num in the list
*/
SegmentItem* Memory_getSegment(ProcessMemoryLayout* pmem, int segment_num);

/**
   adds if possible a memory segment to the process, whose segment id is segment_num.
   the segment has base and limit set to 0 (no size)
*/
SegmentItem* Memory_addSegment(ProcessMemoryLayout* pmem,
			       uint32_t segment_id,
			       uint32_t base,
			       uint32_t limit);

/**
   removes a segment to a process and frees all pages occupied by a segment
   it updates the pid in the memory list, to reflect that the segment has been augmented
*/
int Memory_destroySegment(SegmentItem* segment);


uint32_t Memory_freePages();

void Memory_destroyProcessMemoryLayout(ProcessMemoryLayout* pmem);

SegmentItem* Memory_moveSegment(SegmentItem* item, uint32_t new_base);

