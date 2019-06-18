In this folder

- real user space preemption using sigalarm and ucontext
- cpu state is stored in a variable ucontext
  - each context has a stack and a set of registers
  - context can be obtained (getcontext)
  - jumped into (setcontext)
  - swapped (swapcontext)
  - initialized for a function (makecontext)

- timer implemented with sigalarm
- each process has its own stack
- the signal handler has its own stack
- there is a global incremental timer that monitors
  the timer invocations
  
What to see
1. the context creation mechanism
   files:
   - disastrOS.c
     functions:
     - disastrOS_start: initializes contexts for
       signal handling, system, exit and init process
   - disastrOS_spawn.c
      functions:
      - internal_spawm initializes context for new thread, and gives ot a stack
	
2. the context swapping mechanism
   files:
   - disastros.c,
     functions:
     - timerHandler: saves current cpu context, and
       jumps to interrupt context
       which shares the same stack of the system
     - timerInterrupt: restores the context of the
       currently running process

3. the sigalarm installation
   files:
   - disastrOS.c
     functions:
     - disastrOS_start: installs a signal handler

4. how to use it
   files:
   - disastrOS_c
