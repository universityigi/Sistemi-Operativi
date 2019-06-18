#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

#define MAX_NUM_ITEMS 20

typedef struct {
  ListItem list;
  int info;
} IntListItem;

// print method (late binding)
void IntListItem_print(struct ListItem* item){
  printf("[int] %d\n",((IntListItem*)item)->info);
}

// vtable for int list (an INSTANCE)
ListItemOps int_list_item_ops={
  .dtor_fn=0,
  .print_fn=IntListItem_print
};


typedef struct {
  ListItem list;
  float f;
} FloatListItem;

// print method (late binding)
void FloatListItem_print(struct ListItem* item){
  printf("[float] %f\n",((FloatListItem*)item)->f);
}

// vtable for float list (an INSTANCE)
ListItemOps float_list_item_ops={
  .dtor_fn=0,
  .print_fn=FloatListItem_print
};

int main(int argc, char** argv) {
  // we populate the list, by inserting MAX_NUM_ITEMS
  ListHead head;
  List_init(&head);
  for (int i=0; i<MAX_NUM_ITEMS; ++i){
    ListItem* item=0;
    // the even elements are int, the odd elements are float
    if (i&0x1) {
      FloatListItem* new_element=(FloatListItem*)malloc(sizeof(FloatListItem));
      ListItem_construct((ListItem*) new_element, &float_list_item_ops);
      new_element->f=i/2.0;
      item=(ListItem*) new_element;
    } else {
      IntListItem* new_element=(IntListItem*)malloc(sizeof(IntListItem));
      ListItem_construct((ListItem*) new_element, &int_list_item_ops);
      new_element->info=i;
      item=(ListItem*) new_element;
    }
    List_insert(&head, head.last, item);
  }
  List_print(&head);

  printf("removing odd elements");
  ListItem* aux=head.first;
  int k=0;
  while(aux){
    ListItem* item=aux;
    aux=aux->next;
    if (k%2){
      List_detach(&head, item);
      free(item);
    }
    ++k;
  }
  List_print(&head);
  
  printf("removing from the head, half of the list");
  int size=head.size;
  k=0;
  while(head.first && k<size/2){
    ListItem* item=List_detach(&head, head.first);
    assert(item);
    free(item);
    ++k;
  }
  List_print(&head);
  
  printf("removing from the tail the rest of the list, until it has 1 element");
  while(head.first && head.size>1){
    ListItem* item=List_detach(&head, head.last);
    assert(item);
    free(item);
  }

  List_print(&head);
  
  printf("removing last element");
  ListItem* item=List_detach(&head, head.last);
  assert(item);
  free(item);
  List_print(&head);
  
}
