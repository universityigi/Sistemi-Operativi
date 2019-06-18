#include <stdio.h>
#define MAX_ACTIONS 10

int run=1;
//declare a function pointer type void f(int)
typedef void (*ActionPtrFn)(int);

void actionFn0(int ev) {
  printf("Action 0, handling event %d\n", ev);
}

void actionFn1(int ev) {
  printf("Action 1, handling event %d\n", ev);
}

void actionFnDefault(int ev) {
  printf("default action, handling event %d\n", ev);
}

void actionFnQuit(int ev) {
  printf("quitting %d\n", ev);
  run = 0;
}

// array of pointers to functions
ActionPtrFn actions[MAX_ACTIONS];

int main(int argc, char** argv) {
  for (int i=0; i<MAX_ACTIONS; ++i)
    actions[i]=actionFnDefault;

  actions[0]=actionFn0;
  actions[1]=actionFn1;
  actions[8]=actionFn0;
  actions[9]=actionFnQuit;
  while(run) {
    int v;
    scanf("%d",&v);
    if (v<0||v>=MAX_ACTIONS) {
      printf("invalid index %d",v);
      continue;
    }
    (*actions[v])(v);
  }
}
