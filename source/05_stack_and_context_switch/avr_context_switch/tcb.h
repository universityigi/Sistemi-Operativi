#pragma once
#include <stdint.h>
#include <stddef.h>

#define OK     0
#define ERROR -1

typedef uint8_t* Pointer;
typedef void (* ThreadFn)(uint32_t thread_args);

typedef enum {Running=0x0, Terminated=0x1, Ready=0x2} ThreadStatus;

// thread control block
typedef struct TCB {
  Pointer sp_save_ptr;
  
  ThreadFn thread_fn;
  uint32_t thread_arg;

  struct TCB* next;
  struct TCB* prev;

  Pointer stack_bottom;         /* Pointer to bottom of stack allocation */
  uint32_t stack_size;          /* Size of stack allocation in bytes */
  ThreadStatus status;
} TCB;


void TCB_create(TCB* tcb, Pointer stack_top, ThreadFn thread_fn, uint32_t thread_arg);
