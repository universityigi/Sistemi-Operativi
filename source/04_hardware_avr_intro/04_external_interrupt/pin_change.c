#include <util/delay.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "../avr_common/uart.h" // this includes the printf and initializes it

#define PIN_MASK 0x0F // last four bit of PORT B (50-53)

volatile uint8_t previous_pins;
volatile uint8_t current_pins;

volatile uint8_t int_occurred=0;
volatile uint16_t int_count=0;

// interrupt routine for position PCINT0
ISR(PCINT0_vect) {
  previous_pins=current_pins;
  current_pins=PINB&PIN_MASK;
  int_occurred=1;
  int_count=1;
}


int main(void){
  printf_init(); 
  DDRB &= ~PIN_MASK; //set PIN_MASK pins as input
  PORTB |= PIN_MASK; //enable pull up resistors
  PCICR |= (1 << PCIE0); // set interrupt on change, looking up PCMSK0
  PCMSK0 |= PIN_MASK;   // set PCINT0 to trigger an interrupt on state change 
  sei();
  while(1){
    while (! int_occurred);
    // we reset the flag;
    int_occurred=0;
    printf("int %u, p:%x, c:%x!\n", int_count, previous_pins, current_pins);
  }
}
