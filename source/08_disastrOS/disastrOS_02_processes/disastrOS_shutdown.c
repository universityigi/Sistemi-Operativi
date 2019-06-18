#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"


void internal_shutdown(){
  shutdown_now=1;
  setcontext(&main_context);
}
