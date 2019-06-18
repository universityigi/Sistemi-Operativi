#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "polimorphic_list.h"
#include "polimorphic_list_types.h"
#include "pool_allocator.h"

#define MAX_NUM_ITEMS 16  

int main(int argc, char** argv) {
  //ia initialize the pool allocator;
  //ia since it has fixed size, we have to set the size
  //ia of the allocator to the maximum size of the possible entry
  //ia in this example we suppose to have only FloatListItem, therefore
  //ia the comparison will be the following:
  int max_item_size = -1;
  if (sizeof(IntListItem) < sizeof(FloatListItem)) {
    max_item_size = sizeof(FloatListItem);
  } else {
    max_item_size = sizeof(IntListItem);
  }
  if (max_item_size < 0) {
    printf("something went terribly wrong, exit\n");
    exit(EXIT_FAILURE);
  }

  //ia allocate a buffer of the right dimension
  const int max_buffer_size = MAX_NUM_ITEMS*(max_item_size+sizeof(int));
  char buffer[max_buffer_size];
  memset(buffer, 0, max_buffer_size); //ia just in case

  printf("slab allocator configuration:\n");
  printf("max_item_size   = %d\n", max_item_size);
  printf("max_buffer_size = %d\n", max_buffer_size);    

  //ia initialize an allocator
  PoolAllocator allocator;
  PoolAllocatorResult allocator_result;
  printf("slab allocator initialization...");
  allocator_result = PoolAllocator_init(&allocator,
                                        max_item_size,
                                        MAX_NUM_ITEMS,
                                        buffer,
                                        max_buffer_size);
  printf("%s\n",PoolAllocator_strerror(allocator_result));


  //ia from now on it is the same exercise of before :)
  ListHead head;
  List_init(&head);
  for (int i=0; i<MAX_NUM_ITEMS; ++i){
    ListItem* item=0;
    // the even elements are int, the odd elements are float
    if (i&0x1) {
      FloatListItem* new_element = (FloatListItem*)PoolAllocator_getBlock(&allocator);
      ListItem_construct((ListItem*) new_element, &float_list_item_ops);
      new_element->info=i/2.0;
      item=(ListItem*) new_element;
    } else {
      IntListItem* new_element = (IntListItem*)PoolAllocator_getBlock(&allocator);
      ListItem_construct((ListItem*) new_element, &int_list_item_ops);
      new_element->info=i;
      item=(ListItem*) new_element;
    }
    List_insert(&head, head.last, item);
  }
  List_print(&head);

  printf("removing odd elements\n");
  ListItem* aux=head.first;
  int k=0;
  while(aux){
    ListItem* item=aux;
    aux=aux->next;
    if (k%2){
      List_detach(&head, item);
      allocator_result = PoolAllocator_releaseBlock(&allocator, item);
      printf("%s\n", PoolAllocator_strerror(allocator_result));
    }
    ++k;
  }
  List_print(&head);
  
  printf("removing from the head, half of the list\n");
  int size=head.size;
  k=0;
  while(head.first && k<size/2){
    ListItem* item=List_detach(&head, head.first);
    assert(item);
    allocator_result = PoolAllocator_releaseBlock(&allocator, item);
    printf("%s\n", PoolAllocator_strerror(allocator_result));
    ++k;
  }
  List_print(&head);
  
  printf("removing from the tail the rest of the list, until it has 1 element\n");
  while(head.first && head.size>1){
    ListItem* item=List_detach(&head, head.last);
    assert(item);
    allocator_result = PoolAllocator_releaseBlock(&allocator, item);
    printf("%s\n", PoolAllocator_strerror(allocator_result));
  }

  List_print(&head);
  
  printf("removing last element\n");
  ListItem* item=List_detach(&head, head.last);
  assert(item);
  allocator_result = PoolAllocator_releaseBlock(&allocator, item);
  printf("%s\n", PoolAllocator_strerror(allocator_result));
  List_print(&head);

  printf("\ntest ended! :)\n");  
  return 0;
}
