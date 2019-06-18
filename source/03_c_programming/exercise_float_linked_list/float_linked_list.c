#include <stdio.h>
#include <stdlib.h>
#include "float_linked_list.h"

void FloatListItem_construct(FloatListItem* f_item) {
  if (!f_item) {
    printf("[FloatListItem_construct] invalid argument, exit\n");
    exit(EXIT_FAILURE);
  }

  f_item->list.prev = 0;
  f_item->list.next = 0;
}



void FloatList_print(ListHead* head) {
  ListItem* aux = head->first;
  printf("[ ");

  while(aux) {
    FloatListItem* float_item = (FloatListItem*)aux;
    printf("%f ", float_item->value);
    aux = aux->next;
  }

  printf("]\n");
}

float FloatList_sum(ListHead* head) {
  float value = 0.0f;
  ListItem* aux = head->first;
  while(aux) {
    FloatListItem* float_item = (FloatListItem*)aux;
    value += float_item->value;
    aux = aux->next;
  }
  return value;
}


void FloatList_destroy(ListHead* head) {
  while(head->first){
    FloatListItem* f_item = (FloatListItem*)List_detach(head, head->first);
    free(f_item);
  }
}



void FMatrix_print(ListHead* matrix_head) {
  ListItem* aux = matrix_head->first;

  while(aux) {
    FMatrixRow* row = (FMatrixRow*)aux;
    FloatList_print(&row->columns);
    aux = aux->next;
  }
    
}

void FMatrix_sumRows(ListHead* matrix_head,
                     ListHead* sum_list) {
  if (sum_list->first) {
    printf("[FMatrix_sumRows] error, sum_list must be empty, exit\n");
    exit(EXIT_FAILURE);
  }

  List_init(sum_list);

  ListItem* aux = matrix_head->first;
  while(aux) {
    FMatrixRow* row = (FMatrixRow*)aux;

    float sum = FloatList_sum(&row->columns);
    FloatListItem* sum_item = (FloatListItem*)malloc(sizeof(FloatListItem));
    FloatListItem_construct(sum_item);
    sum_item->value = sum;
    List_insert(sum_list, sum_list->last, (ListItem*)sum_item);
    
    aux = aux->next;
  }  
}

void FMatrix_destroy(ListHead* matrix_head) {
  if (!matrix_head) {
    return;
  }

  while(matrix_head->first) {
    FMatrixRow* row = (FMatrixRow*)List_detach(matrix_head, matrix_head->first);
    FloatList_destroy(&row->columns);
    free(row);
  }  
}

const float FMatrix_at(ListHead* matrix_head,
                       const int row_idx,
                       const int col_idx) {
  if (!matrix_head) {
    printf("[FMatrix_at] invalid matrix, exit");
    exit(EXIT_FAILURE);
  }

  FMatrixRow* first_row = (FMatrixRow*)matrix_head->first;
  
  const int num_rows = matrix_head->size;
  const int num_cols = first_row->columns.size;

  if (row_idx >= num_rows ||
      col_idx >= num_cols) {
    printf("[FMatrix_at] index exceeds matrix dimensions, exit");
    exit(EXIT_FAILURE);
  }

  int r = 0;
  ListItem* aux = matrix_head->first;
  while(aux && r != row_idx) {
    aux = aux->next;
    ++r;
  }
  FMatrixRow* current_row = (FMatrixRow*)aux;
  
  int c = 0;
  ListItem* col_aux = current_row->columns.first;
  while (col_aux && c != col_idx) {
    col_aux = col_aux->next;
    ++c;
  }
  
  FloatListItem* current_col = (FloatListItem*)col_aux;
  return current_col->value;  
}


