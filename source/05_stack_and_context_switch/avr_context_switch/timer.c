#include "timer.h"

// main scheduler function
extern void schedule(void);

/**
 * \b avrInitSystemTickTimer
 *
 * Initialise the system tick timer. Uses the AVR's timer1 facility.
 *
 * @return None
 */
void timerStart ( void )
{
    /* Set timer 1 compare match value for configured system tick,
     * with a prescaler of 256. We will get a compare match 1A
     * interrupt on every system tick, in which we must call the
     * OS's system tick handler. */
    OCR1A = (AVR_CPU_HZ / 256 / SYSTEM_TICKS_PER_SEC);

    /* Enable compare match 1A interrupt */
#ifdef TIMSK
    TIMSK = _BV(OCIE1A);
#else
    TIMSK1 = _BV(OCIE1A);
#endif

    /* Set prescaler 256 */
    TCCR1B = _BV(CS12) | _BV(WGM12);
}


// timer interrupt
ISR (TIMER1_COMPA_vect)
{
    schedule();
}
