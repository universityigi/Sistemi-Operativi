#include <stdio.h>

typedef struct RelocationTableEntry{
  char name[8];
  void (*fn_text)();
} RelocationTableEntry;

RelocationTableEntry *myTable;

void _pino(){
  printf("i am pino;\n");
}

void _gino(){
  printf("i am gino;\n");
}

void _pemponio(){
  printf("i am pemponio;\n");
}


void _pinoLoader(){
  printf("loading pino;\n");
  myTable[0].fn_text=_pino;
  (*myTable[0].fn_text)();
}

void _ginoLoader(){
  printf("loading gino;\n");
  myTable[1].fn_text=_gino;
  (*myTable[1].fn_text)();
}

void _pemponioLoader(){
  printf("loading pemponio;\n");
  myTable[2].fn_text=_pemponio;
  (*myTable[2].fn_text)();
}

RelocationTableEntry table[]={
  {"pino", _pinoLoader},
  {"gino", _ginoLoader},
  {"pemponio", _pemponioLoader}
};



// PINO IS AT OFFSET 3 OF RELOCATION TABLE
void pino(){
  (*table[0].fn_text)();
}

void gino(){
  (*table[1].fn_text)();
}

void pemponio(){
  (*table[2].fn_text)();
}

int main() {
  myTable = table;
  pino();
  gino();
  pemponio();

  pino();
  gino();
  pemponio();

}


