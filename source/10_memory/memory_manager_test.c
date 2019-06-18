#include <stdio.h>
#include "memory_manager.h"

int main(int argc, char** argv){
  Memory_init();
  // create first process
  ProcessMemoryLayout* p1=Memory_addProcessLayout(0);
  // create a segment if id 0, spanning from address 0 to location 10
  SegmentItem* s11=Memory_addSegment(p1, 0, 0, 10);
  ProcessMemoryLayout_print(p1);

  // create a segment if id 1, spanning from address 20 to location 40
  SegmentItem* s12=Memory_addSegment(p1, 1, 20, 20);
  ProcessMemoryLayout_print(p1);
  
  //create second process, with the same segment layout
  ProcessMemoryLayout* p2=Memory_addProcessLayout(1);
  // create a segment if id 0, spanning from address 0 to location 10
  SegmentItem* s21=Memory_addSegment(p2, 0, 0, 10);
  // create a segment if id 1, spanning from address 20 to location 40
  SegmentItem* s22=Memory_addSegment(p2, 1, 20, 20);
  
  ProcessMemoryLayout_print(p2);

  printf("moving segment!!!\n");
  SegmentItem* s22_moved=Memory_moveSegment(s22, 100);

  ProcessMemoryLayout_print(p2);

  // attempting an illegal move
  s22_moved=Memory_moveSegment(s22, 0);
  printf("this should be 0 %ld\n", s22_moved);
  
  //destroy the segment s1 of process p1
  Memory_destroySegment(s11);
  ProcessMemoryLayout_print(p1);
  ProcessMemoryLayout_print(p2);
  printf("free memory %d\n", Memory_freePages());

  Memory_destroyProcessMemoryLayout(p1);

  printf("free memory %d\n", Memory_freePages());
  
  Memory_destroyProcessMemoryLayout(p2);
  printf("free memory %d\n", Memory_freePages());
  
  Memory_shutdown();
}
