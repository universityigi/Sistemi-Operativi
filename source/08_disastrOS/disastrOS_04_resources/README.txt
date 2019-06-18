THIS IS INCOMPLETE

In this folder

- resource management system
  we implemented the infrastructure to handle descriptors and files
- a "resource is uniquely identified in the system
  it can be created, opened or closed by one or more files
  it keeps track of who is usingit
- a process keeps track of the open resources through descriptors

1. the resource structures and allocation
   files: disastrOS_resource.*

2. the descriptor structures and allocation
   files: disastrOS_resource.*

3. the PCB is modified by adding a list of open descriptors
   files: pcb.h, pcb.c

4. the resources appear in the global variables
   files: disastrOS.c

5. new system calls to manage resources
   files:
   - disastrOS_syscalls.h
   - disastrOS_resource_open.c
   - disastrOS_resource_close.c
   - disastrOS_resource_destroy.c

6. new syscalls are added to the infrastructure
   files:
   - disastrOS.c
     functions:
     -disastrOS_start
