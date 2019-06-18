#include <avr/interrupt.h>
#include <avr/io.h>
#include <assert.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>
#include "tcb.h"
#include "tcb_list.h"
#include "uart.h"
#include "atomport_asm.h"
#include "scheduler.h"
#define THREAD_STACK_SIZE 256
#define IDLE_STACK_SIZE 128



//statically allocated variables where we put our stuff

TCB idle_tcb;
uint8_t idle_stack[IDLE_STACK_SIZE];
void idle_fn(uint32_t thread_arg __attribute__((unused))){
  while(1) {
    cli();
    printf("i\n");
    sei();
    _delay_ms(10);
  }
}

TCB p1_tcb;
uint8_t p1_stack[THREAD_STACK_SIZE];
void p1_fn(uint32_t arg __attribute__((unused))){
  while(1){
    cli();
    printf("p1\n");
    sei();
    _delay_ms(10);
  }
}

TCB p2_tcb;
uint8_t p2_stack[THREAD_STACK_SIZE];
void p2_fn(uint32_t arg __attribute__((unused))){
  while(1){
    cli();
    printf("p2\n");
    sei();
    _delay_ms(10);
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

  
  TCBList_enqueue(&running_queue, &p1_tcb);
  TCBList_enqueue(&running_queue, &p2_tcb);
  TCBList_enqueue(&running_queue, &idle_tcb);

  printf("starting\n");
  startSchedule();
}
