#include <stdio.h>

//declare a function pointer that handles an event

typedef void (*ActionPtrFn)(void);

// pointer to function
ActionPtrFn action; // A function can be a *PARAMETER*;

void actionFn0();
void actionFn1();
void actionFn2();

void actionFn0(void) {
  printf("handing  0\n");
  action=actionFn1;
}

void actionFn1(void) {
  printf("handing  1\n");
  action=actionFn2;
}

void actionFn2(void) {
  printf("handing  2\n");
  action=actionFn0;
}

int main(int argc, char** argv) {
  action=actionFn1;
  while(1) {
    int value;
    getchar();
    (*action)();
  }
}
