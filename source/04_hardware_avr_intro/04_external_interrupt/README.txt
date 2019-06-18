# sample programs to use external interrupts

int0: attach a wire to gnd, and with the other extrema connect/disconnect
      pin 21 (scl/PD0).
      On cutecom the events are counted through interrupts

pin_change: attach a wire to gnd, and disturb the pins 50-53
     A single interrupt on pin change is set for these pins
     both on falling and rising edges
     Once again, watch the result on cutecom
