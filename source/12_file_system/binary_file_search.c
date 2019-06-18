#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef int (*CompareFn)(void* v1, void* v2);

int binaryFileSearch(int fd, void* item, int item_size, CompareFn compare){
  //1 we get the size of the file
  struct stat stats;
  fstat(fd, &stats);

  // from the size, we determine the number of records
  int size=stats.st_size;
  printf("size: %d, item_size: %d\n", size, item_size);
  //printf("the file has size %d\n", (int)size);

  //we determine the number of records
  int num_records=size/item_size;
  assert(!(size%item_size));

  
  int low=0;
  int high=num_records-1;
  
  char buffer[item_size];
  while(high>low){
    int middle=(high+low)/2;

    // we fetch the item in the file at current pos
    off_t offset=lseek(fd, middle*item_size, SEEK_SET);
    if (offset<0){
      printf("bad things happened\n");
      return -1;
    }
    int bytes_read=read(fd, buffer, item_size);
    if (bytes_read!=item_size){
      printf("invalid read\n");
      return -1;
    }
    // we compare the read element with the one
    // passed as argument
    int cmp_result=(*compare)(item,buffer);
    if (! cmp_result)
      return middle;
    
    int half=(high-low)/2;
    if (! half)
      return -1;
    if (cmp_result<0) {
      // the element we look for is lower than the middle
      // we continue the search in the lower half
      high=half;
    } else {
      // the element we look for is lower than the middle
      // we continue the search in the upper half
      low=half;
    }
  }
  return -1;
}


int binaryFileWrite(int fd, void* src, int item_size, int pos){
  off_t offset=lseek(fd, pos*item_size, SEEK_SET);
  if (offset<0) {
    ftruncate(fd, (pos+1)*item_size);
    offset=lseek(fd, pos*item_size, SEEK_SET);
  }
  int written_bytes=write(fd, src, item_size);
  if (item_size!=written_bytes)
    return -1;
  return 0;
}

int binaryFileRead(int fd, void* dest, int item_size, int pos){
  size_t desired_offset=pos*item_size;
  off_t offset=lseek(fd, desired_offset, SEEK_SET);
  if (offset<0) {
    return -1;
  }
  int read_bytes=read(fd, dest, item_size);
  if (read_bytes!=item_size){
    return -1;
  }
  return 0;
}
