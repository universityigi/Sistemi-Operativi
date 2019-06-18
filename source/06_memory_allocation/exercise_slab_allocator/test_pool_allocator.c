#include <stdio.h>
#include "pool_allocator.h"

// object size=4K
# define item_size 4096

// 1024 blocks
#define num_items 16

// buffer should contain also bookkeeping information
#define buffer_size num_items*(item_size+sizeof(int))

// we allocate buffer in .bss
char buffer[buffer_size];

PoolAllocator allocator;

int main(int argc, char** argv) {
  printf("initializing... ");
  PoolAllocatorResult init_result=PoolAllocator_init(&allocator,
						     item_size,
						     num_items,
						     buffer,
						     buffer_size);
  printf("%s\n",PoolAllocator_strerror(init_result));

  // we allocate_all memory, and a bit more
  
  void* blocks[num_items+10];
  for (int i=0; i<num_items+10; ++i){
    void* block=PoolAllocator_getBlock(&allocator);
    blocks[i]=block;
    printf("allocation %d, block %p, size%d\n", i, block, allocator.size);  
  }

  // we release all memory
  for (int i=0; i<num_items+10; ++i){
    void* block=blocks[i];
    if (block){
      printf("releasing... idx: %d, block %p, free %d ... ",
	     i, block, allocator.size);
      PoolAllocatorResult release_result=PoolAllocator_releaseBlock(&allocator, block);
      printf("%s\n", PoolAllocator_strerror(release_result));
    }
  }

  // we release all memory again (should get a bunch of errors)
  for (int i=0; i<num_items+10; ++i){
    void* block=blocks[i];
    if (block){
      printf("releasing... idx: %d, block %p, free %d ... ",
	     i, block, allocator.size);
      PoolAllocatorResult release_result=PoolAllocator_releaseBlock(&allocator, block);
      printf("%s\n", PoolAllocator_strerror(release_result));
    }
  }
  
  // we allocate half of the memory, and release it in reverse order
  for (int i=0; i<num_items-5; ++i){
    void* block=PoolAllocator_getBlock(&allocator);
    blocks[i]=block;
    printf("allocation %d, block %p, size%d\n", i, block, allocator.size);  
  }

  for (int i=num_items-1; i>=0; --i){
    void* block=blocks[i];
    if (block){
      printf("releasing... idx: %d, block %p, free %d ... ",
	     i, block, allocator.size);
      PoolAllocatorResult release_result=PoolAllocator_releaseBlock(&allocator, block);
      printf("%s\n", PoolAllocator_strerror(release_result));
    }
  }

  // we allocate all  memory,
  // and release only even blocks, in reverse order
  // release odd blocks in reverse order
  for (int i=0; i<num_items; ++i){
    void* block=PoolAllocator_getBlock(&allocator);
    blocks[i]=block;
    printf("allocation %d, block %p, size%d\n", i, block, allocator.size);  
  }

  for (int i=num_items-1; i>=0; i-=2){
    void* block=blocks[i];
    if (block){
      printf("releasing... idx: %d, block %p, free %d ... ",
	     i, block, allocator.size);
      PoolAllocatorResult release_result=PoolAllocator_releaseBlock(&allocator, block);
      printf("%s\n", PoolAllocator_strerror(release_result));
    }
  }

  for (int i=num_items-2; i>=0; i-=2){
    void* block=blocks[i];
    if (block){
      printf("releasing... idx: %d, block %p, free %d ... ",
	     i, block, allocator.size);
      PoolAllocatorResult release_result=PoolAllocator_releaseBlock(&allocator, block);
      printf("%s\n", PoolAllocator_strerror(release_result));
    }
  }


  
}
