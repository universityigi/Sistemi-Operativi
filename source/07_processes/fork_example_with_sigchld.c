#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>


/*
  Spawns two processes: the parent and the child
  Both execute a useless loop for a certain number of rounds
  (see  parent and child)
  One of the two will die earlier.
  The parent is notified about the death of the child by SIGCHLD;
  The child is notified about the death of the parent by SIGHUP;
*/

const char parent_prefix[]="parent";
const char child_prefix[]="child";
const char* prefix=parent_prefix;
pid_t pid;

const int num_rounds_parent=10;
const int num_rounds_child=1;
void childFunction() {
  for (int round_num=0; round_num<num_rounds_child; round_num++) {
    printf("%s looping, pid: %d, round: %d \n", prefix, pid, round_num);
    sleep(1);
  }
}

void parentFunction() {
  for (int round_num=0; round_num<num_rounds_parent; round_num++) {
    printf("%s looping, pid: %d, round: %d \n", prefix, pid, round_num);
    sleep(1);
  }
}

void sigchld_handler(int signal) {
  printf("SIGNAL %s got signal %d, child is dead\n", prefix, signal);
}

void sighup_handler(int signal) {
  printf("SIGNAL %s got signal %d, parent is dead\n", prefix, signal);
}

int main(int argc, char** argv) {
  pid=getpid(); // here we store the process id
  printf("%s started, pid: %d\n", prefix, pid);

  printf("%s now forking\n", prefix);
  pid_t fork_result=fork(); // here we store the result of the fork;
  
  if(fork_result==0){ // we are in the child process
    prefix=child_prefix;
    pid=getpid(); 
    printf("%s started, pid: %d\n", prefix, pid);

    // Basic of handling signals
    // 1. declare a pair of variables to hold
    //    current and new state of the signal
    struct sigaction new_action, old_action;
    
    // 2. prepare the new signal handler (a struct)
    // 2a. copy the function pointer to the handler routine in the sa_handler field
    new_action.sa_handler = sighup_handler;
    // 2b. tell not to block any other signal
    sigemptyset (&new_action.sa_mask);
    // 2c. the default behavior is fine
    new_action.sa_flags = 0;
    // 3 retrieve the status of the previous handles
    //   so that ifsomething goes wrong you can recover it
    sigaction (SIGHUP, NULL, &old_action);

    // 4 we check if there was an handler different from sig_ign installed
    //   if this is the case, we restore the original behavior and we quit.
    if (old_action.sa_handler != SIG_IGN) {
      sigaction (SIGHUP, &new_action, NULL);
      printf("%s installing sighup handler successful\n", prefix);
    } else {
      printf("%s handler was not empty, aborting \n", prefix);
      exit(-1);
    }

    
    childFunction();
  } else {
    struct sigaction new_action, old_action;

    /* Set up the structure to specify the new action. */
    new_action.sa_handler = sigchld_handler;
    sigemptyset (&new_action.sa_mask);
    new_action.sa_flags = 0;
    sigaction (SIGCHLD, NULL, &old_action);
    if (old_action.sa_handler != SIG_IGN) {
      sigaction (SIGCHLD, &new_action, NULL);
      printf("%s installing sigchld handler successful\n", prefix);
    } else {
      printf("%s handler was not empty, aborting \n", prefix);
      exit(-1);
    }
    printf("%s continuing execution, pid: %d\n", prefix, pid);
    parentFunction();
    printf("%s sending sighup to %d\n", prefix, fork_result);
    kill(fork_result, SIGHUP); // on linux we should explicitly raise sighup
  }
  printf("%s terminating, pid: %d\n", prefix, pid);
  exit(0);
}
