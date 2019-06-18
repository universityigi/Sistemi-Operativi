#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "float_linked_list.h"

#define NUM_ELEMENTS 5

int main (int argc, char** argv) {

  ListHead head;
  List_init(&head);

  //ia init things
  printf("initialize list of float with size %d", NUM_ELEMENTS);
  for (int i = 0; i < NUM_ELEMENTS; ++i) {
    FloatListItem* f_item = (FloatListItem*)malloc(sizeof(FloatListItem));
    if (!f_item) {
      printf("memory is a bad person, exit\n");
      exit(EXIT_FAILURE);
    }
    
    f_item->list.prev = NULL;
    f_item->list.next = NULL;
    f_item->value = i + 0.5f;

    ListItem* res = List_insert(&head, head.last, (ListItem*)f_item);
    if (!res) {
      printf("impossible to insert new element, exit\n");
      exit(EXIT_FAILURE);
    }
    
    printf(".");
  }
  printf("done\n");
  printf("list size: %d\n", head.size);

  //ia print the list
  printf("print the list\n");
  FloatList_print(&head);

  //ia compute the sum
  printf("sum = %f\n", FloatList_sum(&head));

  //ia checkout things
  printf("checkout remaining items");
  while(head.first){
    FloatListItem* f_item = (FloatListItem*)List_detach(&head, head.first);
    free(f_item);
    printf(".");
  }
  printf("done\n");
  printf("list size: %d\n\n", head.size);


  //ia going with the matrix thing
  printf("initialize a (%d x %d) matrix", NUM_ELEMENTS, NUM_ELEMENTS);
  ListHead matrix;
  List_init(&matrix);
  
  for (int r_idx = 0; r_idx < NUM_ELEMENTS; ++r_idx) {
    // printf("[ ");

    //ia allocate a row
    FMatrixRow* row = (FMatrixRow*)malloc(sizeof(FMatrixRow));
    row->list.prev = NULL;
    row->list.next = NULL;
    List_init(&row->columns);
    //ia insert a row in the shitty matrix
    ListItem* res_row = List_insert(&matrix, matrix.last, (ListItem*)row);
    if (!res_row)
      exit(EXIT_FAILURE);
    
    for (int c_idx = 0; c_idx < NUM_ELEMENTS; ++c_idx) {
      float value = 0.5*r_idx+c_idx;
      // printf("%f ", value);
      printf(".");

      FloatListItem* f_item = (FloatListItem*)malloc(sizeof(FloatListItem));
      FloatListItem_construct(f_item);
      f_item->value = value;
      List_insert(&row->columns, row->columns.last, (ListItem*)f_item);
    }
    // printf("]\n");
  }
  printf("done\n");

  //ia print out the matrix
  printf("printing the matrix\n");
  FMatrix_print(&matrix);
  printf("\n");

  //ia generate the list with the sums of each row
  ListHead rows_sums;
  List_init(&rows_sums);
  FMatrix_sumRows(&matrix, &rows_sums);

  printf("printing the sum of each row\n");
  FloatList_print(&rows_sums);
  printf("\n");

  //ia print the value 3,3
  int r = 3, c = 3;
  printf("matrix->at[%d, %d] = %f\n\n", r, c, FMatrix_at(&matrix, r, c));
  printf("\n");

  //ia checkout things
  printf("checkout things\n");
  FloatList_destroy(&rows_sums);
  FMatrix_destroy(&matrix);  
  
  return 0;
}
