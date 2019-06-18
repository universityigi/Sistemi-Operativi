#pragma once

enum PoolAllocatorResult{
  Success=0x0,
  NotEnoughMemory=-1,
  UnalignedFree=-2,
  OutOfRange=-3,
  DoubleFree=-4
} ;

typedef enum PoolAllocatorResult PoolAllocatorResult;

typedef struct PoolAllocator{
  
  char* buffer;        //contiguous buffer managed by the system
  int*  free_list;     //list of linked objects
  int buffer_size;     //size of the buffer in bytes

  int size;            //number of free blocks
  int size_max;        //maximum number of blocks
  int item_size;       //size of a block
  
  int first_idx;       //pointer to the first bucket
  int bucket_size;     // size of a bucket
} PoolAllocator;

PoolAllocatorResult PoolAllocator_init(PoolAllocator* allocator,
			int item_size,
			int num_items,
			char* memory_block,
			int memory_size);

void* PoolAllocator_getBlock(PoolAllocator* allocator);

PoolAllocatorResult PoolAllocator_releaseBlock(PoolAllocator* allocator, void* block);
			
const char* PoolAllocator_strerror(PoolAllocatorResult result);
