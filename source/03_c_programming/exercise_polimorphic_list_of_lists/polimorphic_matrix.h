#pragma once

#include "polimorphic_list.h"

typedef struct ListListItem {
  ListItem list;
  ListHead info;
} ListListItem;

void ListListItem_print(ListItem* item);
void ListListItem_construct(ListListItem* l_item_);


typedef struct {
  ListItem list;
  int info;
} IntListItem;

void IntListItem_print(ListItem* item);
void IntListItem_construct(IntListItem* l_item_);


typedef struct {
  ListItem list;
  float info;
} FloatListItem;

void FloatListItem_print(ListItem* item);
void FloatListItem_construct(FloatListItem* l_item_);





