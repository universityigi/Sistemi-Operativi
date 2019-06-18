#include "pool_allocator.h"

static const int NullIdx=-1;
static const int DetachedIdx=-2;

static const char* PoolAllocator_strerrors[]=
  {"Success",
   "NotEnoughMemory",
   "UnalignedFree",
   "OutOfRange",
   "DoubleFree",
   0
  };

const char* PoolAllocator_strerror(PoolAllocatorResult result) {
  return PoolAllocator_strerrors[-result];
}

PoolAllocatorResult PoolAllocator_init(PoolAllocator* a,
		       int item_size,
		       int num_items,
		       char* memory_block,
		       int memory_size) {

  // we first check if we have enough memory
  // for the bookkeeping
  int requested_size= num_items*(item_size+sizeof(int));
  if (memory_size<requested_size)
    return NotEnoughMemory;

  a->item_size=item_size;
  a->size=num_items;
  a->buffer_size=item_size*num_items;
  a->size_max = num_items;
  
  a->buffer=memory_block; // the upper part of the buffer is used as memory
  a->free_list= (int*)(memory_block+item_size*num_items); // the lower part is for bookkeeping

  // now we populate the free list by constructing a linked list
  for (int i=0; i<a->size-1; ++i){
    a->free_list[i]=i+1;
  }
  // set the last element to "NULL" 
  a->free_list[a->size-1] = NullIdx;
  a->first_idx=0;
  return Success;
}

void* PoolAllocator_getBlock(PoolAllocator* a) {
  if (a->first_idx==-1)
    return 0;

  // we need to remove the first bucket from the list

  int detached_idx = a->first_idx;
  // advance the head
  a->first_idx=a->free_list[a->first_idx];
  --a->size;
  
  a->free_list[detached_idx]=DetachedIdx;
  
  //now we retrieve the pointer in the item buffer
  char* block_address=a->buffer+(detached_idx*a->item_size);
  return block_address;
}

PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* a, void* block_){
  //we need to find the index from the address
  char* block=(char*) block_;
  int offset=block - a->buffer;

  //sanity check, we need to be aligned to the block boundaries
  if (offset%a->item_size)
    return UnalignedFree;

  int idx=offset/a->item_size;

  //sanity check, are we inside the buffer?
  if (idx<0 || idx>=a->size_max)
    return OutOfRange;

  //is the block detached?
  if (a->free_list[idx]!=DetachedIdx)
    return DoubleFree;

  // all fine, we insert in the head
  a->free_list[idx]=a->first_idx;
  a->first_idx=idx;
  ++a->size;
  return Success;
}
