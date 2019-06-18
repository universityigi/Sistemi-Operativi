#pragma once

//ia declare a function pointer type void f(unsigned char)
typedef void (*ActionPtrFn)(unsigned char);

//ia global declaration of the action function ptr
extern ActionPtrFn action;

//ia global declaration of a variable that will tell us
//ia how many cycles we have to remain in status S4
extern unsigned int counter;

//ia functions of the automata
void actionFnS1(unsigned char input);
void actionFnS2(unsigned char input);
void actionFnS3(unsigned char input);
void actionFnS4(unsigned char input);
void actionFnS5(unsigned char input);
