#include "tcb.h"
#include <avr/interrupt.h>

extern TCB* current_tcb;

// we need a void function not to mess up with parameters on the stack
static void _trampoline(void){
  sei();
  /* Call the thread entry point */
  if (current_tcb && current_tcb->thread_fn) {
    (*current_tcb->thread_fn)(current_tcb->thread_arg);
  }

  // set the thread to terminated, when the above function finishes
  current_tcb->status=Terminated;
}

void TCB_create(TCB* tcb, Pointer stack_top, ThreadFn thread_fn, uint32_t thread_arg){
  //initialize variables
  tcb->thread_fn=thread_fn;
  tcb->thread_arg=thread_arg;
  tcb->prev=NULL;
  tcb->next=NULL;
  tcb->status=Ready;
  
  /** prepare stack for process **/
  
  uint8_t *stack_ptr = (uint8_t *)stack_top;

  /** write the return address of the function being called (the trampoline)*/
  *stack_ptr-- = (uint8_t)((uint16_t)_trampoline & 0xFF);
  *stack_ptr-- = (uint8_t)(((uint16_t)_trampoline >> 8) & 0xFF);

  // this is for the devices with more than 64K of program memory
#ifdef __AVR_3_BYTE_PC__
  *stack_ptr-- = 0;
#endif


  /**
   * Store starting register values for R2-R17, R28-R29
   */
  *stack_ptr-- = 0x00;    /* R2 */
  *stack_ptr-- = 0x00;    /* R3 */
  *stack_ptr-- = 0x00;    /* R4 */
  *stack_ptr-- = 0x00;    /* R5 */
  *stack_ptr-- = 0x00;    /* R6 */
  *stack_ptr-- = 0x00;    /* R7 */
  *stack_ptr-- = 0x00;    /* R8 */
  *stack_ptr-- = 0x00;    /* R9 */
  *stack_ptr-- = 0x00;    /* R10 */
  *stack_ptr-- = 0x00;    /* R11 */
  *stack_ptr-- = 0x00;    /* R12 */
  *stack_ptr-- = 0x00;    /* R13 */
  *stack_ptr-- = 0x00;    /* R14 */
  *stack_ptr-- = 0x00;    /* R15 */
  *stack_ptr-- = 0x00;    /* R16 */
  *stack_ptr-- = 0x00;    /* R17 */
  *stack_ptr-- = 0x00;    /* R28 */
  *stack_ptr-- = 0x00;    /* R29 */

    /**
     * On devices with large program space we also context switch RAMPZ, EIND.
     */
#ifdef __AVR_3_BYTE_PC__
  *stack_ptr-- = 0x00;    /* RAMPZ */
  *stack_ptr-- = 0x00;    /* EIND */
#endif

  /**
     * All thread context has now been initialised. Save the current
     * stack pointer to the thread's TCB so it knows where to start
     * looking when the thread is started.
     */
  tcb->sp_save_ptr = stack_ptr;

}
