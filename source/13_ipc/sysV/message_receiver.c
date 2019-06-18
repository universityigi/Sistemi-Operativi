#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "constants.h"


/* simple example of a message sender

*/

int queue_id=-1; // this contains the descriptor for the queue
                 // invalid at the beginnig

void cleanup(int retval) {
  printf("cleanup, attempting to remove the queue\n");
  if (queue_id<0)
    return;
  
  struct msqid_ds status;
  int msgctl_return=msgctl(queue_id, IPC_RMID, &status);
  if (msgctl_return<0) {
    printf("%s\n", strerror(errno));
  }
  exit(retval);
}

int main(int argc, char** argv) {
  if(argc<2) {
    printf("usage %s <int>", argv[0]);
    printf(" <int>: common identifier if message queue");
    exit (-1);
  }
  
  int key=atoi(argv[1]);
  printf("create to message queue for key %d\n", key);
  queue_id=msgget(key, IPC_CREAT|0666); // we make a new one if not here
  if (queue_id<0) {
    printf("%s\n", strerror(errno));
    cleanup(-1);
  }

  char buffer_big_enough[MAX_MSG_SIZE];
  while(1){
    // we check the status of the queue
    // this is not mandatory
    struct msqid_ds status;
    int msgctl_return=msgctl(queue_id, IPC_STAT, &status);
    if (msgctl_return<0) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }
    printf("Size: %ld messages\n", status.msg_qnum);


    // receive ANY message in the queue
    int message_size=msgrcv(queue_id, buffer_big_enough, MAX_MSG_SIZE, 0, 0);
    if (message_size<0){
      printf("%s\n", strerror(errno));
      exit(-1);
    }
    // we got a message in the buffer
    // we cast it to header (which is the first struct in the pool)
    MessageHeader* header=(MessageHeader*)buffer_big_enough;
    switch (header->type) {
    case 1: // we send the message 1
      {
      MessageOne* message_one = (MessageOne*)buffer_big_enough;
      printf("MessageOne: { seq:%d, values:[%d,%d]\n",
	     message_one->header.seq,
	     message_one->values[0],
	     message_one->values[1]);
      }
      break;
    case 2: // we send the message two
      {
      MessageTwo* message_two = (MessageTwo*)buffer_big_enough;
      printf("MessageTwo: { seq:%d, values:[%f,%f,%f]\n",
	     message_two->header.seq,
	     message_two->values[0],
	     message_two->values[1],
	     message_two->values[2]);
      }
      break;
    }
  }
}
