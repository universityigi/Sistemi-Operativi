#pragma once
#include "linked_list.h"

typedef struct BuddyListItem {
  ListItem list;
  size_t tree_node;
  int level; // level for the buddy
  int start; // start of memory
  int end;   // end of memory
  struct BuddyListItem* buddy_ptr;
  struct Buddy
} BuddyListItem;

inline int level(size_t tree_node){
  return (int)floor(log2(tree_node));
};

inline int buddy(int tree_node){
  if (tree_node&0x1){
    return tree_node-1;
  }
  return tree_node+1;
}

inline int parent(int tree_node){
  return tree_node/2;
}



// creates list items using pool allocator inside buddy
BuddyListItem* BuddyListItem_alloc(BuddyAllocator* allocator);

//erases list items using pool allocator inside buddy
void BuddyListItem_free(BuddyAllocator* allocator, BuddyListItem* item);


BuddyListItem* BuddyListItem_alloc(int level, int start){
  BuddyListItem* item=(BuddyListItem*)malloc(sizeof(BuddyListItem));
  item->list.prev=0;
  item->list.next=0;
  item->level=level;
  item->start=start;
  item->end=1<<(NUM_BUDDY_LEVELS-level-1)+start;
  return item;
};

void BuddyListItem_free(BuddyListItem* item){
  free(item);
}

BuddyAllocator_init(BuddyAllocator* allocator) {
  // all lists are populated with an empty list
  // the list at lowest level has a region convering the entire memory
  for (int i = 0; i<NUM_BUDDY_LEVELS; ++i) {
    List_init(allocator->levels+i);
  }
  BuddyListItem* root=BuddyListItem_alloc(0,0);
  List_insert(allocator->levels,NULL,root);
}

BuddyListItem* BuddyAllocator_get(BuddyAllocator* allocator, int level) {
  // if we have a buddy for that level, we return it;
  if (allocator->levels[level].size) {
    ListItem* item=List_detach(allocator->levels+level, allocator->levels[level].first);
    return (BuddyListItem*) item;
  }

  // otherwise we get a buddy from the higher level
  // if existing;
  BuddyListItem* upper=BuddyAllocator_get(allocator, level-1);
  if (! upper)
    return 0;

  // we split the buddy in two
  BuddyListItem* first_item=BuddyListItem_alloc(level, upper.start);
  BuddyListItem* second_item=BuddyListItem_alloc(level, first_item.end);
  BuddyListItem_free(upper);

  List_insert(allocator->levels+level, allocator->levels[level].last);
  return first_item;
  // we insert the second in the current list
  // and we return the first
}
