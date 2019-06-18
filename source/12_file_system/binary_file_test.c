#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "binary_file_search.h"

typedef struct {
  char family_name[128];
  char name[128];
} SampleStruct;

void SampleStruct_init(SampleStruct* dest,
		       char* family_name,
		       char* name){
  strcpy(dest->family_name, family_name);
  strcpy(dest->name, name);
}

int SampleStruct_compare(void* a, void* b){
  SampleStruct* sa=(SampleStruct*) a;
  SampleStruct* sb=(SampleStruct*) b;
  int cmp1=strcmp(sa->family_name, sb->family_name);
  if (cmp1)
    return cmp1;
  return strcmp(sa->name, sb->name);
}


int main(int argc, char** argv){
  if (argc<2){
    printf("binary_test <file>");
  }
  int fd=open(argv[1], O_CREAT|O_RDWR,0666);
  SampleStruct v;
  SampleStruct_init(&v,"AA","aa");
  write(fd, &v, sizeof(v));
  SampleStruct_init(&v,"CC","cc");
  write(fd, &v, sizeof(v));
  SampleStruct_init(&v,"DD","DD");
  write(fd, &v, sizeof(v));
  SampleStruct_init(&v,"EE","ee");
  write(fd, &v, sizeof(v));
  SampleStruct_init(&v,"KK","lklklkl");
  write(fd, &v, sizeof(v));
  close(fd);

  

  fd=open(argv[1], O_RDONLY,0666);
  int i=4; // read in reverse order!!
  while(!binaryFileRead(fd, &v, sizeof(SampleStruct), i)){
    printf("name: %s, family_name:%s\n", v.name, v.family_name);
    --i;
  }
  close(fd);

  fd=open(argv[1], O_RDONLY,0666);
  SampleStruct_init(&v, "DD", "DD");
  int pos=binaryFileSearch(fd, &v, sizeof(SampleStruct), SampleStruct_compare);
  printf("found pos:%d\n", pos);

  SampleStruct_init(&v, "BB", "DD");
  pos=binaryFileSearch(fd, &v, sizeof(SampleStruct), SampleStruct_compare);
  printf("found pos:%d\n", pos);

  close(fd);
  
}
