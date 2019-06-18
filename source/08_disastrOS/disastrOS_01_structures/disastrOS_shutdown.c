#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"


void internal_shutdown(){
  assert(0 && "shutdown not implemented"); 
}
