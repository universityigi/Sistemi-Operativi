#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "disastrOS_resource.h"
#include "disastrOS_descriptor.h"

void internal_destroyResource(){
  int id=running->syscall_args[0];

  // find the resource in with the id
  Resource* res=ResourceList_byId(&resources_list, id);
  if (! res){
    running->syscall_retvalue=DSOS_ERESOURCECLOSE;
    return;
  }

  // ensure the resource is not used by any process
  if(res->descriptors_ptrs.size){
    running->syscall_retvalue=DSOS_ERESOURCEINUSE;
    return;
  }

  res=(Resource*) List_detach(&resources_list, (ListItem*) res);
  assert(res);
  Resource_free(res);
  running->syscall_retvalue=0;
}
