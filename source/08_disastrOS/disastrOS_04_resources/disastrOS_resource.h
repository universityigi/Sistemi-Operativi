#pragma once
#include "linked_list.h"
#include "disastrOS_pcb.h"


typedef struct {
  ListItem list;
  int id;
  int type;
  ListHead descriptors_ptrs;
} Resource;

void Resource_init();

Resource* Resource_alloc(int id, int type);
int Resource_free(Resource* resource);

typedef ListHead ResourceList;

Resource* ResourceList_byId(ResourceList* l, int id);

void ResourceList_print(ListHead* l);
