#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 

  // we will use timer 4
  // this disables all PWM and interrupts
  // connected with timer
  TCCR4A=0;
  
  // this sets the prescaler to divide the clock by 1024
  TCCR4B=(1 << CS42)|(1<<CS40);

  while(1){
    uint16_t timer_val=TCNT4; // we read the timer value
    printf("count %u\n", timer_val);
    _delay_ms(100); // from delay.h, wait 1 sec
  }
  
}
