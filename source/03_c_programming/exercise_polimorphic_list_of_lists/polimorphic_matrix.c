#include <stdio.h>
#include <stdlib.h>

#include "polimorphic_matrix.h"


void ListListItem_print(ListItem* item_) {
  ListListItem* l_item = (ListListItem*)item_;
  List_print(&l_item->info);
}

void ListListItem_destroy(ListItem* item_) {
  ListListItem* l_item = (ListListItem*)item_;
  List_destroy(&l_item->info);
}

ListItemOps list_list_item_ops={
  .dtor_fn = ListListItem_destroy,
  .print_fn = ListListItem_print
};

void ListListItem_construct(ListListItem* item_) {
  ListItem_construct((ListItem*)item_, &list_list_item_ops);
  List_init(&item_->info);
}


void IntListItem_print(struct ListItem* item){
  printf("[int] %d\n",((IntListItem*)item)->info);
}

// vtable for int list (an INSTANCE)
ListItemOps int_list_item_ops={
  .dtor_fn=0,
  .print_fn=IntListItem_print
};

void IntListItem_construct(IntListItem* item_) {
  ListItem_construct((ListItem*)item_, &int_list_item_ops);
  item_->info = 0;
}


// print method (late binding)
void FloatListItem_print(struct ListItem* item){
  printf("[float] %f\n",((FloatListItem*)item)->info);
}

// vtable for float list (an INSTANCE)
ListItemOps float_list_item_ops={
  .dtor_fn=0,
  .print_fn=FloatListItem_print
};

void FloatListItem_construct(FloatListItem* item_) {
  ListItem_construct((ListItem*)item_, &float_list_item_ops);
  item_->info = 0.0f;
}


