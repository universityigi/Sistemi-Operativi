#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 

  // the LED is connected to pin 13
  // that is the bit 7 of port b
  const uint8_t mask=(1<<7);
  // we configure the pin as output
  DDRB |= mask;
  int k=0;
  while(1){
    printf("led %d\n", (k&1));
    if (k&1)
      PORTB=mask;
    else
      PORTB=0;
    _delay_ms(1000); // from delay.h, wait 1 sec
    ++k;
  }
  
}
