In this folder

- handles wait, (fake) fork and exit
- no preemption, no task management

What to see
   
1. the PCB, with all structures for holding children and cpu state
   (ucontext, unused)
   files: disastros_pcb*

2. system initialization
   files:
   - disastrOS.c
     disastrOS_start: system initializaton
     		      population of system call table
		      passing control to first process
3. syscall mechanism
   files:
   - disastrOS.c
     functions:
     - disastrOS_syscall:  "assembles" the syscall parameters
       in a fake block (normally done in CPU, we access to PCB directly)
     - disastrOS_trap: simulates entering in kernel mode,
       fetches parameters from PCB, invokes call

4. forking
   files:
   -disastrOS_fork.c
    functions:
    - internal_fork
      creates a new pcb and put is in ready list
      updates the structures of creating PCB

5. waiting
   files:
   - disastrOS_wait.c
     functions:
     - internal_wait:
       Puts the calling process in waiting state for child termination.
       If child is already dead, it gives immediately control
       to the parent and passes the pid and the ret value of the
       dead child in the syscall return.
   
6. exiting
   files:
   - disastrOS_exit.c
     functions:
     - internal_exit:
       Stops the execution of the caller.
       If parent was waiting for child termination, it gives
       control to the parent, (that was waiting),
       and sets the pid and retval of died process
       to parent syscall return.
       If the parent was not waiting puts the process in waiting
       state and sets the next process to be executed
       
3. the example
   files:
   - disastrOS_test.c

   simulates a sequence of OS operations and writes to the
   console the system state while running
