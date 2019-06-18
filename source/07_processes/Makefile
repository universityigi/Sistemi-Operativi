CC=gcc
CCOPTS=-std=gnu99
BINS=fork_example\
     fork_example_with_sigchld\
     fork_and_exec\
     vfork_and_exec\
     vfork_exec_and_env

.phony: clean all

all: $(BINS)

fork_example:	fork_example.c
	$(CC) -$(CCOPTS) -o $@ $^

fork_example_with_sigchld:	fork_example_with_sigchld.c
	$(CC) -$(CCOPTS) -o $@ $<

fork_and_exec:	fork_and_exec.c
	$(CC) -$(CCOPTS) -o $@ $^

vfork_and_exec:	vfork_and_exec.c
	$(CC) -$(CCOPTS) -o $@ $^

vfork_exec_and_env:	vfork_exec_and_env.c
	$(CC) -$(CCOPTS) -o $@ $^

clean:
	rm -rf *~ $(BINS)

