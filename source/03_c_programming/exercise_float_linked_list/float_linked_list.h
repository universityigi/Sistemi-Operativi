#pragma once
#include "linked_list.h"

//! float list item
typedef struct FloatListItem {
  ListItem list;
  float value;
} FloatListItem;

void FloatListItem_construct(FloatListItem* item);


//! list of floats methods
void FloatList_print(ListHead* head);
float FloatList_sum(ListHead* head);
void FloatList_destroy(ListHead* head);


//ia matrix of floats as list of columns
typedef struct FMatrixRow {
  ListItem list;
  ListHead columns;
} FMatrixRow;

void FMatrix_print(ListHead* matrix_head);
void FMatrix_sumRows(ListHead* matrix_head,
                     ListHead* sum_list);
void FMatrix_destroy(ListHead* matrix_head);
//ia bonus
const float FMatrix_at(ListHead* matrix_head,
                       const int row_idx,
                       const int col_idx);



