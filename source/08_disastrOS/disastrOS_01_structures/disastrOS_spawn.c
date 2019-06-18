#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

// creates a new instance of the running_process
// and puts it in the ready list
// returns the pid of the child
// it starts a function in the form of void f();
void internal_spawn(){
  assert(0 && "spawn not implemented, need real system");
}
