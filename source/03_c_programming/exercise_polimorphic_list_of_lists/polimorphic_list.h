#pragma once

// forward declaration
// shuts up the compiler
struct ListItem;

// definition of a type for a function pointer in the form
// void function(struct ListItem*);
// used for our print prototype
typedef void (*ListItemPrintFn)(struct ListItem*);

// definition of a type for a function pointer in the form
// void function(struct ListItem*);
// used for our dtor prototype
typedef void (*ListItemDestroyFn)(struct ListItem*);

// virtual method table for the linked list
// contains function pointers to the linked list operations
typedef struct {
  ListItemDestroyFn dtor_fn;
  ListItemPrintFn   print_fn;
} ListItemOps;

typedef struct ListItem {
  struct ListItem* prev;
  struct ListItem* next;
  ListItemOps* ops; // pointer to virtual method table
} ListItem;

// exposed function that crawls in the virtual method table
// and calls the appropriate methods if they exist
void ListItem_destroy(ListItem* item);
void ListItem_print(ListItem* item);

// constructor (generic), installs an instance of virtual
// method table
void ListItem_construct(ListItem* item, ListItemOps* ops);

typedef struct ListHead {
  ListItem* first;
  ListItem* last;
  int size;
} ListHead;

void List_init(ListHead* head);
ListItem* List_find(ListHead* head, ListItem* item);
ListItem* List_insert(ListHead* head, ListItem* previous, ListItem* item);
ListItem* List_detach(ListHead* head, ListItem* item);
void List_print(ListHead* head);
void List_destroy(ListHead* head);
