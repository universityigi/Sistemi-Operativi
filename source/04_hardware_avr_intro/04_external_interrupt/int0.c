#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it

volatile uint8_t interrupt_occurred=0;
uint16_t int_count=0;
ISR(INT0_vect) {
  interrupt_occurred=1;
  int_count++;
}

int main(void){
  printf_init(); 
  DDRD=0x0; // all pins on port b set as input
  PORTD=0x1; // pull_up on port b

  // enable interrupt 0
  EIMSK |=1<<INT0;

  // trigger int0 on rising edge
  EICRA= 1<<ISC01 | 1<<ISC00;
  sei();
  while(1){
    while (! interrupt_occurred);
    // we reset the flag;
    interrupt_occurred=0;
    printf("int %u!\n", int_count);
  }
}
