#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdio.h>
// we will see this in a next episode
size_t getFilesize(const char* filename) {
  struct stat st;
  stat(filename, &st);
  return st.st_size;
}

int main(int argc, char** argv) {
  size_t filesize = getFilesize(argv[1]);

  // syscall to open a file
  int fd = open(argv[1], O_RDONLY, 0);
  assert(fd != -1);

  
  //Execute mmap
  char* file_memory = (char*) mmap(NULL,
				   filesize,
				   PROT_READ|PROT_WRITE,
				   MAP_PRIVATE | MAP_POPULATE,
				   fd,
				   0);

  
  assert(file_memory != MAP_FAILED);

  for (int i=0; i<filesize; ++i){
    file_memory[i]++;
    printf("%c",file_memory[i]);
  }
  
  //Cleanup
  msync(file_memory, filesize, MS_SYNC);
  int rc = munmap(file_memory, filesize);
  assert(rc == 0);
  close(fd);
}
