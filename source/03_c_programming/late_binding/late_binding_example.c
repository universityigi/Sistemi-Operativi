#include <stdio.h>

struct A; // forward declaration of A;
void (*A_PrintFnPtr)(struct A*); //pointer to print fn;
void A_print_impl(struct A* a){printf("A\n");} // A print function
void B_print_impl(struct A* a){printf("B\n");} // B print function

// A VMT (same type as B VMT since no methods are added in B)
// if B adds methods B_VMT inherits from A_VMT
// overriden methods overwrite the corresponding pointer
typedef struct { 
  A_PrintFnPtr print_fn;
} A_ops;

// A class
typedef struct {
  A_ops* ops;
} A;

// VMT is inherited
typedef struct {
  A parent;
} B;

// global variables representing vmt
// the print_fn field is initialized on creation
A_ops a_ops = {.print_fn=A_print_impl};
B_ops b_ops = {.print_fn=B_print_impl};

// wrapper, crawls in VMT and calls right function
void A_print(A* a_ptr) {
  (*a_ptr->ops->print_fn)(a_ptr);
}

int main(){
  A a1={.a_ops=&a_ops};   // declare and set ptr to vmt
  A a2={.a_ops=&a_ops}; 
  B b1={.parent.a_ops=&b_ops};
  B b2={.parent.a_ops=&b_ops};

  A* a_ptr = &a1;
  A_print(a_ptr);
  
  a_ptr = (A*) &b1;
  A_print(a_ptr);

  A* a_ptr = &a2;
  A_print(a_ptr);

  a_ptr = (A*) &b2;
  A_print(a_ptr);

}
