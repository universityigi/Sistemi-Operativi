#include <assert.h>
#include <stdio.h>
#include "disastrOS_resource.h"
#include "disastrOS_descriptor.h"
#include "pool_allocator.h"
#include "linked_list.h"

#define RESOURCE_SIZE sizeof(Resource)
#define RESOURCE_MEMSIZE (sizeof(Resource)+sizeof(int))
#define RESOURCE_BUFFER_SIZE MAX_NUM_RESOURCES*RESOURCE_MEMSIZE

static char _resources_buffer[RESOURCE_BUFFER_SIZE];
static PoolAllocator _resources_allocator;

void Resource_init(){
    int result=PoolAllocator_init(& _resources_allocator,
				  RESOURCE_SIZE,
				  MAX_NUM_RESOURCES,
				  _resources_buffer,
				  RESOURCE_BUFFER_SIZE);
    assert(! result);
}

Resource* Resource_alloc(int id, int type){
  Resource* r=(Resource*) PoolAllocator_getBlock(&_resources_allocator);
  if (!r)
    return 0;
  r->list.prev=r->list.next=0;
  r->id=id;
  r->type=type;
  List_init(&r->descriptors_ptrs);
  return r;
}

int Resource_free(Resource* r) {
  assert(r->descriptors_ptrs.first==0);
  assert(r->descriptors_ptrs.last==0);
  return PoolAllocator_releaseBlock(&_resources_allocator, r);
}

Resource* ResourceList_byId(ResourceList* l, int id) {
  ListItem* aux=l->first;
  while(aux){
    Resource* r=(Resource*)aux;
    if (r->id==id)
      return r;
    aux=aux->next;
  }
  return 0;
}

void Resource_print(Resource* r) {
  printf("id: %d, type:%d, pids:", r->id, r->type);
  DescriptorPtrList_print(&r->descriptors_ptrs);
}

void ResourceList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("{\n");
  while(aux){
    Resource* r=(Resource*)aux;
    printf("\t");
    Resource_print(r);
    if(aux->next)
      printf(",");
    printf("\n");
    aux=aux->next;
  }
  printf("}\n");
}
