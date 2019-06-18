#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"

void internal_fork() {
  assert(0 && "FORK NOT IMPLEMENTED IN REAL SYSTEM, NO MMU");
}
