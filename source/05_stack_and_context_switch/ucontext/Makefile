CC=gcc
CCOPTS=--std=gnu99 -g -Wall 

BINS=context_example

#disastros_test

.phony: clean all


all:	$(BINS)


context_example: context_example.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
