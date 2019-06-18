#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char** argv) {
  // create a shared memory object at key argv[1]

  char* resource_name=argv[1];
  int fd=shm_open(resource_name, O_RDONLY, 0666);
  if (fd<0){
    printf("cannot link to shared memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }
  int SHMEM_SIZE=0;

  struct stat shm_status;
  int fstat_result = fstat(fd, &shm_status); /* To obtain file size */
  if (fstat_result<0){
    printf("cannot get stats from memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }
  
  SHMEM_SIZE = shm_status.st_size;
  
  /*
  void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
  */
  void * my_memory_area = mmap(NULL, SHMEM_SIZE, PROT_READ, MAP_SHARED,
			       fd, 0);
  while (1) {
    char* buffer=(char*) my_memory_area;
    printf("%s\n", buffer);
    usleep(100000);
  }
  
  int unlink_result=shm_unlink(resource_name);
  if (unlink_result<0) {
    printf("cannot unlink shared memory object, error: %s \n", sys_errlist[errno]);
    exit(-1);
  }

}
