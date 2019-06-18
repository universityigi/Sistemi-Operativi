#include <stdio.h>
#include "polimorphic_list.h"

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


void IntListItem_construct(IntListItem* item_) {
  ListItem_construct((ListItem*)item_, &int_list_item_ops);
  item_->info = 0;
}

typedef struct {
  ListItem list;
  float info;
} FloatListItem;

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
