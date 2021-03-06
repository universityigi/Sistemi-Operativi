#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


/**
   spawns N instances of an executable
*/

//The one  below is the null terminated array containing the variables in the environment
extern char** environ; // black magic here 

int main(int argc, char** argv) {
  if (argc<3) {
    printf("usage %s <int> <path> <args>\n", argv[0]);
    printf(" <int> number of instances\n");
    printf(" <path> executable to launch\n");
    printf(" <args> arguments passed to each instance of the executable\n");
  }
  char* prog_path=argv[2];
  int num_instances=atoi(argv[1]);
  int active_instances=0;
  printf("starting program %s in %d instances\n", prog_path, num_instances);

  char* path=getenv("PATH");
  printf(" the current path is %s\n", path);
  
  for (int i=0; i<num_instances; ++i){
    pid_t child_pid=vfork();
    if(! child_pid){
      int result=execvpe(prog_path, argv+2, environ);
      if (result) {
	printf("something wrong with exec errno=%s\n", strerror(errno));
      }
    } else
      active_instances++;

  }
  int status;
  while(active_instances) {
    pid_t child_pid = wait(&status);
    printf("son %d  died, morning\n", child_pid);
    active_instances--;
  }
  printf(" launcher terminating\n");
  return 0;
}
