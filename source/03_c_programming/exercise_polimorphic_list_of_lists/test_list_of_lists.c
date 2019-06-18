#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "polimorphic_matrix.h"

#define NUM_ROWS 5
#define NUM_COLS 4

int main(int argc, char** argv) {
  ListHead list_of_lists;
  List_init(&list_of_lists);

  for (int r = 0; r < NUM_ROWS; ++r) {
    ListListItem* l_item = (ListListItem*)malloc(sizeof(ListListItem));
    ListListItem_construct(l_item);
    List_insert(&list_of_lists, list_of_lists.last, (ListItem*)l_item);
    
    for (int c = 0; c < NUM_COLS; ++c) {
      FloatListItem* f_item = (FloatListItem*)malloc(sizeof(FloatListItem));
      FloatListItem_construct(f_item);

      f_item->info = r*c*0.5;
      List_insert(&l_item->info, l_item->info.last, (ListItem*)f_item);
    }
  }

  List_print(&list_of_lists);

  List_destroy(&list_of_lists);
  
  return 0;
}
