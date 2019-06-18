#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "../avr_common/uart.h" // this includes the printf and initializes it

int main(void){
  // this initializes the printf/uart thingies
  printf_init(); 

  // we connect the switch to pin 12
  // that is the bit 6 of port b
  
  const uint8_t mask=(1<<6);
  // we configure the pin as input, clearing the bit 6
  DDRB &= ~mask;
  
  // we enable pullup resistor on that pin
  PORTB |= mask;
  
  while(1){
    int key=(PINB&mask)==0; // we extract the bit value of the 6th bit
    printf("switch %02x, %d\n", (int) PORTB, key);
    _delay_ms(500); // from delay.h, wait 1 sec
  }
  
}
