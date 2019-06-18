#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "constants.h"


/* simple example of shared memory writer
*/

int shm_id=-1; // this contains the descriptor for the queue
                 // invalid at the beginnig


int num_trials=100;

int main(int argc, char** argv) {
  if(argc<2) {
    printf("usage %s <int>", argv[0]);
    printf(" <int>: common identifier of shared memory resource");
    exit (-1);
  }
  
  int key=atoi(argv[1]);
  printf("seeking for an existing shared memory  key %d\n", key);
  shm_id=shmget(key, SHARED_MEMORY_SIZE, 0666); // we read and write
  if (shm_id<0) {
    exit(-1);
  }

  printf("retrieving size of shared memory");
  struct shmid_ds status;
  int shmctl_return=shmctl(shm_id, IPC_STAT, &status);
  if (shmctl_return<0) {
    printf("%s\n", strerror(errno));
  }
  printf("the memory has size %ld bytes\n", status.shm_segsz);
  
  
  printf("hooking to the newly created memory\n");
  char* shared_buffer=(char*) shmat(shm_id, NULL, SHM_RDONLY);
  if(! shared_buffer)
    exit(-1);
  
  const MessageOne* msg_one = (MessageOne*) shared_buffer;
  const MessageTwo* msg_two = (MessageTwo*) shared_buffer+sizeof(MessageOne);
  while(1) {
    printf("MessageOne: { seq:%d, values:[%d,%d]\n",
	   msg_one->header.seq,
	   msg_one->values[0],
	   msg_one->values[1]);
    printf("MessageTwo: { seq:%d, values:[%f,%f,%f]\n",
	   msg_two->header.seq,
	   msg_two->values[0],
	   msg_two->values[1],
	   msg_two->values[2]);
    sleep(1);
  }

  int shmdet_result=shmdt(shared_buffer);
  if (shmdet_result<0) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }
  exit(0);
}
