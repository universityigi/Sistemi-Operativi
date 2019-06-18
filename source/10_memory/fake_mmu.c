#include <stdio.h>
#include <assert.h>
#include "bits_macros.h"
#include "fake_mmu.h"

LinearAddress getLinearAddress(MMU* mmu, LogicalAddress logical_address){
  //2. check if the segment is in the segment table
  assert (logical_address.segment_id < mmu->num_segments && "segment out of bounds" );
  
  //2. select the descriptor from the mmu table
  SegmentDescriptor descriptor=mmu->segments[logical_address.segment_id];

  //3. see if the segment is valid
  assert((descriptor.flags) & Valid && "invalid_segment");
  assert((logical_address.page_number <descriptor.limit) && "out_of_segment_limit");

  LinearAddress linear_address;
  linear_address.page_number=descriptor.base+logical_address.page_number;
  linear_address.offset=logical_address.offset;

  //5. return the address
  return linear_address;
}


uint32_t getPhysicalAddress(MMU* mmu, LinearAddress linear_address) {
  //1. get the page number
  PageEntry page_entry=mmu->pages[linear_address.page_number];
  assert( page_entry.flags & Valid && "invalid page");
  uint32_t frame_number=page_entry.frame_number;
  //5. combine the entry of the page table with the offset, and get the physical address
  return (frame_number<<FRAME_NBITS)|linear_address.offset;
}
