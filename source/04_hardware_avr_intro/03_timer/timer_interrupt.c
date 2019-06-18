#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it

volatile uint8_t interrupt_occurred=0;

// our interrupt routine installed in
// interrupt vector position
// corresponding to output compare
// of timer 5

uint16_t int_count=0;
ISR(TIMER5_COMPA_vect) {
  interrupt_occurred=1;
  int_count++;
}

int main(void){
  printf_init(); 
  const int timer_duration_ms=100;
  
  // configure timer
  // set the prescaler to 1024
  TCCR5A = 0;
  TCCR5B = (1 << WGM52) | (1 << CS50) | (1 << CS52); 
  
  // at this count rate
  // 1 ms will correspond do 15.62 counts
  // we set the output compare to an appropriate
  // value so that when the counter reaches that value
  // the interrupt will be triggered
  uint16_t ocrval=(uint16_t)(15.62*timer_duration_ms);

  OCR5A = ocrval;

  // clear int
  cli();
  TIMSK5 |= (1 << OCIE5A);  // enable the timer interrupt
  // enable int
  sei();
  while(1){
    while (! interrupt_occurred);
    // we reset the flag;
    interrupt_occurred=0;
    printf("int %u!\n", int_count);
  }
}
