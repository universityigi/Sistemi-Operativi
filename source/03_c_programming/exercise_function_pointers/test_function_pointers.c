#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include "functions.h"

//ia black magic - for now :)
void sigHandler(int sig_number_);

int main (int argc, char** argv) {
  if (signal(SIGINT, sigHandler) == SIG_ERR)
    printf("error can't catch SIGINT\n");

  while (1) {
    int input;
    
    //ia read from the keyboard in hex 
    printf("enter a value in hex form - es \"ff\"\n");
    scanf("%x", &input);
    printf("input = %02x\n", input);

    //ia let the automata do its thing :)
    (*action)((unsigned char)input);
  }

  return 0;
}

void sigHandler(int sig_number_) {
  if (sig_number_ != SIGINT){
    printf("error, wrong signal\n");
    exit(EXIT_FAILURE);
  }
  
  printf("\nexit\n");
  exit(EXIT_SUCCESS);
}
