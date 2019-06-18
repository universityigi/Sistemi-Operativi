In this folder

- timer awakening mechanism
  we implemented a sleep call that sleeps n interrupt cycles
  this is done by a timer list mechanism, where all the
  alarms are stored in a timer list
- at each timer tick, a global counter is incremented,
  and the processes that were waiting for an alarm to ring
  are awakened and put in ready state
- we need an idle process  
What to see

1. the timer structures and allocation
   files: disastrOS_timer.*
   
2. the PCB is modified by adding a pointer to a timer event
   files: pcb.h, pcb.c

3. the initialization 
   files:
   -disastrOS.c
    functions:
    - disastrOS_start: initializes the system timer list
      and installs a new syscall disastrOS_sleep();

4. sleeping mechanism
   files:
   - disastrOS_sleep.c
     -function internal_sleep
      - checks if a process is eligible to have a timer installed
        creates a timer, adds it to the global timer list,
	and puts the process to sleep

5. awakening mechanism
   - files: disastrOS_schedule.c
     functions:
     - internal_schedule: at each tick checks the timer list
       and puts the processes that were waiting in the running queue
       then executes the regular selection for the next process

6. example file
   - files: disastrOS_test.c
