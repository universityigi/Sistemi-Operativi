#include <assert.h>
#include <stdio.h>
#include "disastrOS_descriptor.h"
#include "pool_allocator.h"
#include "disastrOS_constants.h"

#define DESCRIPTOR_SIZE sizeof(Descriptor)
#define DESCRIPTOR_MEMSIZE (sizeof(Descriptor)+sizeof(int))
#define MAX_NUM_DESCRIPTORS (MAX_NUM_DESCRIPTORS_PER_PROCESS*MAX_NUM_PROCESSES)
#define DESCRIPTOR_BUFFER_SIZE MAX_NUM_DESCRIPTORS*DESCRIPTOR_MEMSIZE

#define DESCRIPTORPTR_SIZE sizeof(DescriptorPtr)
#define DESCRIPTORPTR_MEMSIZE (sizeof(DescriptorPtr)+sizeof(int))
#define DESCRIPTORPTR_BUFFER_SIZE MAX_NUM_DESCRIPTORS*DESCRIPTORPTR_MEMSIZE

static char _descriptor_buffer[DESCRIPTOR_BUFFER_SIZE];
static PoolAllocator _descriptor_allocator;

static char _descriptor_ptr_buffer[DESCRIPTORPTR_BUFFER_SIZE];
static PoolAllocator _descriptor_ptr_allocator;

void Descriptor_init(){
  int result=PoolAllocator_init(& _descriptor_allocator,
				DESCRIPTOR_SIZE,
				MAX_NUM_PROCESSES,
				_descriptor_buffer,
				DESCRIPTOR_BUFFER_SIZE);
  assert(! result);

  result=PoolAllocator_init(& _descriptor_ptr_allocator,
			    DESCRIPTORPTR_SIZE,
			    MAX_NUM_PROCESSES,
			    _descriptor_ptr_buffer,
			    DESCRIPTORPTR_BUFFER_SIZE);
  assert(! result);
}

Descriptor* Descriptor_alloc(int fd, Resource* res, PCB* pcb) {
  Descriptor* d=(Descriptor*)PoolAllocator_getBlock(&_descriptor_allocator);
  if (!d)
    return 0;
  d->list.prev=d->list.next=0;
  d->fd=fd;
  d->resource=res;
  d->pcb=pcb;
  return d;
}

int Descriptor_free(Descriptor* d) {
  return PoolAllocator_releaseBlock(&_descriptor_allocator, d);
}

Descriptor*  DescriptorList_byFd(ListHead* l, int fd){
  ListItem* aux=l->first;
  while(aux){
    Descriptor* d=(Descriptor*)aux;
    if (d->fd==fd)
      return d;
    aux=aux->next;
  }
  return 0;
}

DescriptorPtr* DescriptorPtr_alloc(Descriptor* descriptor) {
  DescriptorPtr* d=PoolAllocator_getBlock(&_descriptor_ptr_allocator);
  if (!d)
    return 0;
  d->list.prev=d->list.next=0;
  d->descriptor=descriptor;
  return d;
}

int DescriptorPtr_free(DescriptorPtr* d){
  return PoolAllocator_releaseBlock(&_descriptor_ptr_allocator, d);
}

void DescriptorList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("[");
  while(aux){
    Descriptor* d=(Descriptor*)aux;
    printf("(fd: %d, rid:%d)",
	   d->fd,
	   d->resource->id);
    if(aux->next)
      printf(", ");
    aux=aux->next;
  }
  printf("]");
}


void DescriptorPtrList_print(ListHead* l){
  ListItem* aux=l->first;
  printf("[");
  while(aux){
    DescriptorPtr* d=(DescriptorPtr*)aux;
    printf("(pid: %d, fd: %d, rid:%d)",
	   d->descriptor->fd,
	   d->descriptor->pcb->pid,
	   d->descriptor->resource->id);
    if(aux->next)
      printf(", ");
    aux=aux->next;
  }
  printf("]");
}
