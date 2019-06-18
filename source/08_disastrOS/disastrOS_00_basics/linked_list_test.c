#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pool_allocator.h"
#include "linked_list.h"

#define MAX_NUM_ITEMS 64
#define _USE_MALLOC_

typedef struct MyListElement{
  ListItem list;
  int info;
} MyListElement;


#ifdef _USE_MALLOC_

void initStructures(){}

MyListElement* MyListElement_allocate() {
  return (MyListElement*) malloc(sizeof(MyListElement));
}

void MyListElement_free(MyListElement* item) {
  free (item);
}

#else //_USE_POOL_ALLOCATOR

#define BUFFER_SIZE MAX_NUM_ITEMS*(sizeof(MyListElement)+sizeof(int))
char my_list_element_buffer[ BUFFER_SIZE ];
PoolAllocator my_list_element_allocator;

void initStructures(){
  int result=PoolAllocator_init(& my_list_element_allocator,
			      sizeof(MyListElement),
			      MAX_NUM_ITEMS,
			      my_list_element_buffer,
				BUFFER_SIZE);
  if (result) {
    printf("PoolAllocator_init: %s\n", PoolAllocator_strerror(result)); 
  }
  assert(! result);
}

MyListElement* MyListElement_allocate() {
  return (MyListElement*) PoolAllocator_getBlock(&my_list_element_allocator);
}

void MyListElement_free(MyListElement* item) {
  int result=PoolAllocator_releaseBlock(&my_list_element_allocator, item);
  if (result) {
    printf("PoolAllocator_init: %s\n", PoolAllocator_strerror(result)); 
  }
  assert(! result);
}
#endif //_USE_MALLOC_

void MyList_print(ListHead* head){
  ListItem* aux=head->first;
  printf("[");
  while(aux){
    MyListElement* element = (MyListElement*) aux;
    printf("%d ", element->info);
    aux=aux->next;
  }
  printf("]\n");
}

int main(int argc, char** argv) {
  initStructures();
  
  // we populate the list, by inserting MAX_NUM_ITEMS
  ListHead head;
  List_init(&head);
  ListItem* items_v[MAX_NUM_ITEMS];
  for (int i=0; i<MAX_NUM_ITEMS; ++i){
    MyListElement* new_element=MyListElement_allocate();
    if (! new_element) {
      printf("out of memory\n");
      break;
    }
    new_element->list.prev=0;
    new_element->list.next=0;
    new_element->info=i;
    ListItem* result=List_insert(&head, head.last, (ListItem*) new_element);
    items_v[i]=result;
    assert(result);
  }
  MyList_print(&head);

  printf("removing odd elements");
  for (int i=0; i<MAX_NUM_ITEMS; i+=2){
    ListItem* item=List_detach(&head, items_v[i]);
    assert(item);
    MyListElement_free((MyListElement*)item);
  }
  MyList_print(&head);
  
  printf("removing from the head, half of the list");
  int size=head.size;
  int k=0;
  while(head.first && k<size/2){
    ListItem* item=List_detach(&head, head.first);
    assert(item);
    MyListElement_free((MyListElement*)item);
    ++k;
  }
  MyList_print(&head);
  
  printf("removing from the tail the rest of the list, until it has 1 element");
  while(head.first && head.size>1){
    ListItem* item=List_detach(&head, head.last);
    assert(item);
    MyListElement_free((MyListElement*)item);
  }

  MyList_print(&head);

  printf("removing last element");
  ListItem* item=List_detach(&head, head.last);
  assert(item);
  MyListElement_free((MyListElement*)item);
  MyList_print(&head);  
  
}
