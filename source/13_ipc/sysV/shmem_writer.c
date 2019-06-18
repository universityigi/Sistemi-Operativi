#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "constants.h"


/* simple example of shared memory reader
*/

int shm_id=-1; // this contains the descriptor for the queue
                 // invalid at the beginnig


void cleanup(int retval) {
  printf("cleanup, attempting to remove the queue\n");
  if (shm_id<0)
    return;
  
  struct shmid_ds status;
  int shmctl_return=shmctl(shm_id, IPC_RMID, &status);
  if (shmctl_return<0) {
    printf("%s\n", strerror(errno));
  }
  exit(retval);
}

int num_trials=100;

int main(int argc, char** argv) {
  if(argc<2) {
    printf("usage %s <int>", argv[0]);
    printf(" <int>: common identifier of shared memory resource");
    exit (-1);
  }
  
  int key=atoi(argv[1]);
  printf("creating a shared memory for key %d\n", key);
  shm_id=shmget(key, SHARED_MEMORY_SIZE, IPC_CREAT|0666); // we read and write
  if (shm_id<0) {
    cleanup(-1);
  }

  printf("hooking to the newly created memory\n");
  char* shared_buffer=(char*) shmat(shm_id, NULL, 0);
  if(! shared_buffer)
    cleanup(-1);
  
  MessageOne* msg_one = (MessageOne*) shared_buffer;
  MessageTwo* msg_two = (MessageTwo*) shared_buffer+sizeof(MessageOne);
  msg_one->header.type=1;
  msg_two->header.type=2;

  int seq=0;
  while(1) {
    msg_one->header.seq=seq;
    msg_two->header.seq=seq;
    
    sleep(1);
    printf(".");
    fflush(stdout);
    ++seq;
  }

  int shmdet_result=shmdt(shared_buffer);
  if (shmdet_result<0) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }
  cleanup(0);
}
