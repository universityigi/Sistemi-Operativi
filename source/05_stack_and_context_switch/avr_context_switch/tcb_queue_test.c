#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include "tcb.h"
#include "tcb_list.h"
#include "uart.h"
#include "scheduler.h"

#define THREAD_STACK_SIZE 256
#define IDLE_STACK_SIZE 128


/* void switchContext(TCB* old_tcb, TCB* new_tcb){ */
/*   new_tcb.status=Running; */
/*   if (old_tcb!=new_tcb){ */
/*     current_tcb=new_tcb; */
/*     asmSwitchContext(old_tcb, new_tcb); */
/*   } */
/* } */

//statically allocated variables where we put our stuff

TCB idle_tcb;
uint8_t idle_stack[IDLE_STACK_SIZE];
void idle_fn(uint32_t thread_arg __attribute__((unused))){
  while(1);
}

TCB p1_tcb;
uint8_t p1_stack[THREAD_STACK_SIZE];
void p1_fn(uint32_t arg __attribute__((unused))){
  while(1){
    cli();
    printf("p1\n");
    sei();
    _delay_ms(100);
  }
}

TCB p2_tcb;
uint8_t p2_stack[THREAD_STACK_SIZE];
void p2_fn(uint32_t arg __attribute__((unused))){
  while(1){
    cli();
    printf("p1\n");
    sei();
    _delay_ms(100);
  }
}

int main(void){
  // we need printf for debugging
  printf_init();

  TCB_create(&idle_tcb,
             idle_stack+IDLE_STACK_SIZE-1,
             idle_fn,
             0);

  TCB_create(&p1_tcb,
             p1_stack+THREAD_STACK_SIZE-1,
             p1_fn,
             0);

  TCB_create(&p2_tcb,
             p2_stack+THREAD_STACK_SIZE-1,
             p2_fn,
             0);

  
  TCBList_enqueue(&running_queue, &idle_tcb);
  TCBList_enqueue(&running_queue, &p1_tcb);
  TCBList_enqueue(&running_queue, &p2_tcb);

  printf("starting\n");
  TCBList_print(&running_queue);
  
  while(1) {
    printf("dequeuing\n");
    current_tcb=TCBList_dequeue(&running_queue);
    printf("current: %p\n",current_tcb);
    TCBList_print(&running_queue);
    _delay_ms(100);
    printf("enqueuing\n");
    TCBList_enqueue(&running_queue, current_tcb);
    TCBList_print(&running_queue);
  }
}
