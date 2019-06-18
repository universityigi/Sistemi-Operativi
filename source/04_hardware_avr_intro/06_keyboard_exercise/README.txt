# this is an example of matrix keyboard
# you will need a wire

The rows of the matrix (output pins) are mapped on PORTA, bits 4:7
The cols of the matrix (input pins) are mapped on PORTV, bits  0:3, with pullups

The program sets low in a cyclic manner only one of
the output bits.
When a pin is low, we can read the row of the keyboard.
The row is mapped such that a bit 0:3 is low if the corresponding
key on that row is pressed.

We monitor the previous status of the keyboard by storing
all pressed/released status of each bit in an uint16 variable.
When a key changes status we emit an event

To test it connect a wire between each pin
26:29 to each pin 22:25

