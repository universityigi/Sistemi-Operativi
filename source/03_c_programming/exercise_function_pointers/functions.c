#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "functions.h"

//ia intialize the automata
ActionPtrFn action = actionFnS1;
unsigned int counter = 0;  

void actionFnS1(unsigned char input) {
  if (input == 0xAA) {
    action = actionFnS2;
    printf("state S2\n");
  } else {
    printf("state S1\n");
  }
}

void actionFnS2(unsigned char input) {
  if (input == 0x55) {
    action = actionFnS3;
    printf("state S3\n");
  } else {
    action = actionFnS1;
    printf("state S1\n");
  }
}

void actionFnS3(unsigned char input) {
  //ia we put the read value in the counter var
  //ia in this way we know how many times we must perform actionFnS4
  counter = (int)input;
  
  action = actionFnS4;
  printf("state S4\n");
}

void actionFnS4(unsigned char input) {
  //ia we remain in S4 until we read <counter> characters
  if (counter > 0) {
    //ia next action and state remain the same as before,
    //ia since we still have to read things
    printf("state S4\thex characher = %02x\n", (int)input);
    
    //ia decrement the counter, since we read a new character
    --counter;
  } else {
    //ia we finished the reading phase, so we can move to the next state
    printf("state S5\n");
    action = actionFnS5;
  }
}

void actionFnS5(unsigned char input) {
  if (input == 0xAA) {
    action = actionFnS2;
    printf("state S2\n");
  } else {
    action = actionFnS1;
    printf("state S1\n");
  }
}

