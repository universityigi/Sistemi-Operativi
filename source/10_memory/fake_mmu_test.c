#include <stdio.h>
#include "fake_mmu.h"

int main(int  argc, char** argv){
  printf("ADDRESS_NBITS: %d, size: %d\n", ADDRESS_NBITS, MAX_MEMORY);
  printf("SEGMENT_NBITS: %d, num_segments: %d\n", SEGMENT_NBITS, SEGMENTS_NUM);
  printf("PAGE_NBITS: %d, num_pages: %d, frame_size:%d\n",
	 PAGE_NBITS,
	 PAGES_NUM,
	 PAGE_SIZE);

  PageEntry pages[PAGES_NUM];
  uint32_t pages_num=PAGES_NUM;

  // we fill the pages array in reverse order, just for fun
  for (int i=0; i<PAGES_NUM; ++i){
    PageEntry* entry=pages+i;
    entry->frame_number=PAGES_NUM-i-1;
    entry->flags=Valid;
  }


  // we divide the memory in 4 contiguous
  SegmentDescriptor segments[4];
  uint32_t segments_num=4;
  segments[0].flags=Valid;
  segments[0].base=0;
  segments[0].limit=PAGES_NUM/4;

  segments[1].flags=Valid;
  segments[1].base=segments[0].limit;
  segments[1].limit=PAGES_NUM/4;

  segments[2].flags=Valid;
  segments[2].base=segments[1].base+segments[1].limit;
  segments[2].limit=PAGES_NUM/4;

  segments[3].flags=Valid;
  segments[3].base=segments[2].base+segments[2].limit;
  segments[3].limit=PAGES_NUM/4;

  MMU mmu;
  mmu.segments=segments;
  mmu.num_segments=segments_num;
  mmu.pages=pages;
  mmu.num_pages=pages_num;


  // we generate a set of linear addresses and see how they are mapped
  for (uint32_t s=0; s<segments_num; ++s){
    printf("in segment %x, base: %x, limit: %x\n",
	   s,
	   segments[s].base,
	   segments[s].limit);
	   
           
    for (uint32_t p=0; p<segments[s].limit; ++p){
      LogicalAddress logical_address;
      logical_address.segment_id=s;
      logical_address.page_number=p;
      logical_address.offset=0x1;
      printf("logical address: [s: %x, p: %x, o: %x] -> ",
	     logical_address.segment_id,
	     logical_address.page_number,
	     logical_address.offset);

      LinearAddress linear_address=getLinearAddress(&mmu, logical_address);
      printf("linear address: [p: %x, o: %x] -> ",
	     linear_address.page_number,
	     linear_address.offset);

      PhysicalAddress physical_address=getPhysicalAddress(&mmu, linear_address);
      printf("physical_address: [%x] \n",
	     physical_address);

    }
  }
    
  return 0;

}
