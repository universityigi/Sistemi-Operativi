#include <avr/interrupt.h>
#include <avr/io.h>

#define SYSTEM_TICKS_PER_SEC            10

/* CPU Frequency */
#ifdef F_CPU
#define AVR_CPU_HZ          F_CPU
#else
#define AVR_CPU_HZ          16000000
#endif

void timerStart ( void );
