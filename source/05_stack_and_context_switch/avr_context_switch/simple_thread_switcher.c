#include <avr/interrupt.h>
#include <avr/io.h>
#include <utils/delay.h>
#include <stdint.h>
#include "tcb.h"
#include "tcb_list.h"
#include "uart.h"


/* void switchContext(TCB* old_tcb, TCB* new_tcb){ */
/*   new_tcb.status=Running; */
/*   if (old_tcb!=new_tcb){ */
/*     current_tcb=new_tcb; */
/*     asmSwitchContext(old_tcb, new_tcb); */
/*   } */
/* } */

//statically allocated variables where we put our stuff
#define THREAD_STACK_SIZE 256
#define IDLE_STACK_SIZE 128

TCB idle_tcb;
uint8_t idle_stack[IDLE_STACK_SIZE];

TCB p1_tcb;
uint8_t p1_stack[THREAD_STACK_SIZE];

TCB p2_tcb;
uint8_t p2_stack[THREAD_STACK_SIZE];


//! global variables

// the (detached) running process
TCB* current_tcb=NULL;

// the running queue
TCBList running_queue;


void main(void){
  int c=0;
  while(1) {
    ++c;
    printf("%d\n", c);
    delay_ms(100);
  }
}
