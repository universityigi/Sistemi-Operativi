#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

/*
  Spawns two processes: the parent and the child
  Both execute a useless loop for a certain number of rounds
  (see  parent and child)
  One of the two will die earlier.
  What happens if the father dies earlier than the child?
  What happens if the child dies earlier than the parent?
*/

const char parent_prefix[]="parent"; 
const char child_prefix[]="child";

// this is overridden by the child upon creation
const char* prefix=parent_prefix;
pid_t pid;

// how many rounds
const int num_rounds_parent=10;
const int num_rounds_child=5;

// inner function executed by the child after parent fork()ed
void childFunction() {
  for (int round_num=0; round_num<num_rounds_child; round_num++) {
    printf("%s looping, pid: %d, round: %d \n", prefix, pid, round_num);
    sleep(1);
  }
}

// inner function executed by the parent after spawning child
void parentFunction() {
  for (int round_num=0; round_num<num_rounds_parent; round_num++) {
    printf("%s looping, pid: %d, round: %d \n", prefix, pid, round_num);
    sleep(1);
  }
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
    childFunction();
  } else {
    printf("%s continuing execution, pid: %d\n", prefix, pid);
    parentFunction();
  }
  printf("%s terminating, pid: %d\n", prefix, pid);
}
