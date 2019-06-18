#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

const int SHMEM_SIZE=1024;

int main(int argc, char** argv) {
  // create a shared memory object at key argv[1]

  char* resource_name=argv[1];
  int fd=shm_open(resource_name, O_RDWR|O_CREAT, 0666);
  if (fd<0){
    printf("cannot create shared memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }
  int ftruncate_result = ftruncate(fd, SHMEM_SIZE);
  if (ftruncate_result<0) {
    printf("cannot truncate shared memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }
  
  /*
  void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
  */
  void * my_memory_area = mmap(NULL, SHMEM_SIZE, PROT_WRITE, MAP_SHARED,
			       fd, 0);
  int num_rounds=100;
  for (int i=0; i<num_rounds; ++i) {
    char* buffer=(char*) my_memory_area;
    sprintf(buffer, "This is the message %d", i);
    printf("writing [%s]\n", buffer);
    sleep(1);
  }
  
  int unlink_result=shm_unlink(resource_name);
  if (unlink_result<0) {
    printf("cannot unlink shared memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }

}
