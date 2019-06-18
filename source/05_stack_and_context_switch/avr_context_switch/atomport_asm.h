#pragma once
#include "tcb.h"

//prototype for assembly functions
void archContextSwitch (TCB *old_tcb_ptr, TCB *new_tcb_ptr);
void archFirstThreadRestore(TCB *new_tcb_ptr);

