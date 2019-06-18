#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "linked_list.h"

#define MAX_NUM_ITEMS 64

typedef struct IntListItem{
  ListItem list;
  int info;
} IntListItem;

void IntList_print(ListHead* head){
  ListItem* aux=head->first;
  printf("[");
  while(aux){
    IntListItem* element = (IntListItem*) aux;
    printf("%d ", element->info);
    aux=aux->next;
  }
  printf("]\n");
}

int main(int argc, char** argv) {
  // we populate the list, by inserting MAX_NUM_ITEMS
  ListHead head;
  List_init(&head);
  for (int i=0; i<MAX_NUM_ITEMS; ++i){
    IntListItem* new_element= (IntListItem*)
      malloc(sizeof(IntListItem));
    if (! new_element) {
      printf("out of memory\n");
      break;
    }
    new_element->list.prev=0;
    new_element->list.next=0;
    new_element->info=i;
    ListItem* result=
      List_insert(&head, head.last, (ListItem*) new_element);
    assert(result);
  }
  IntList_print(&head);

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
  IntList_print(&head);
  
  printf("removing from the head, half of the list");
  int size=head.size;
  k=0;
  while(head.first && k<size/2){
    ListItem* item=List_detach(&head, head.first);
    assert(item);
    free(item);
    ++k;
  }
  IntList_print(&head);
  
  printf("removing from the tail the rest of the list, until it has 1 element");
  while(head.first && head.size>1){
    ListItem* item=List_detach(&head, head.last);
    assert(item);
    free(item);
  }

  IntList_print(&head);

  printf("removing last element");
  ListItem* item=List_detach(&head, head.last);
  assert(item);
  free(item);
  IntList_print(&head);  
  
}
