#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// select a large number of elements

int main(int argc, char** argv){
  if (argc<4) {
    printf ("usage: %s <num_elements> <num_rounds> <sequential>\n", argv[0]);
    return -1;
  }
  int num_elements=atoi(argv[1]);
  int num_rounds=atoi(argv[2]);
  int sequential=atoi(argv[3]);
  printf("running %s\n", argv[0]);
  printf(" num_elements: %d\n", num_elements);
  printf(" num_rounds: %d\n", num_rounds);
  printf(" sequential: %d\n", sequential);
  
  
  int* picks=(int*) malloc (num_elements * sizeof(int));
  int* src=(int*) malloc (num_elements * sizeof(int));
  int* dest=(int*) malloc (num_elements * sizeof(int));
  for (int i=0; i<num_elements; ++i){
    picks[i]=i;
    src[i]=rand();
  }

  if (! sequential) {
    for (int i=0; i<num_elements; ++i){
      int idx1=rand()%num_elements;
      int idx2=rand()%num_elements;
      int aux=picks[idx1];
      picks[idx1]=picks[idx2];
      picks[idx2]=aux;
    }
  }
  
  printf("start\n");
  for (int round=0; round<num_rounds; ++round){
    printf("round %d/%d\n", round, num_rounds);
    for (int i=0; i<num_elements; ++i) {
      int idx=picks[i];
      dest[idx]=src[idx];
    }
  }
  printf("done\n");
  return 0;
  
};
