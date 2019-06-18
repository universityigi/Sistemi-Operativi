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

int num_trials=100;

int main(int argc, char** argv) {
  if(argc<2) {
    printf("usage %s <int>", argv[0]);
    printf(" <int>: common identifier if message queue");
    exit (-1);
  }
  
  int key=atoi(argv[1]);
  printf("hooking to message queue for key %d\n", key);
  int queue_id=msgget(key, 0222); // we hook to a writing queue
  if (queue_id<0) {
    printf("%s\n", strerror(errno));
    exit(-1);
  }

  MessageOne message_one;
  message_one.header.type=1;
  
  MessageTwo message_two;
  message_two.header.type=2;

  for (int i=0; i<num_trials; i++){

    // we check the status of the queue
    // this is not mandatory
    struct msqid_ds status;
    int msgctl_return=msgctl(queue_id, IPC_STAT, &status);
    if (msgctl_return<0) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }
    printf("Size: %ld messages\n", status.msg_qnum);


    
    void* message=0;
    int message_size=0;

    // we prepare to send messages of different types, alternatively
    switch(i&1){
    case 0: // we send the message 1
      printf("sending message one\n");
      message_one.header.seq=i;
      message = &message_one;
      message_size= sizeof(message_one);
      break;
    case 1: // we send the message two
      printf("sending message two\n");
      message_two.header.seq=i;
      message = &message_two;
      message_size= sizeof(message_two);
      break;
    }

    // we send the message
    int msgsnd_return=msgsnd(queue_id, message, message_size, 0);
    if (msgsnd_return<0) {
      printf("%s\n", strerror(errno));
      exit(-1);
    }
    sleep(1);
  }
}
