CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar


BINS=binary_file_test

OBJS=binary_file_search.c

HEADERS=binary_file_search.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

.phony: clean all


all:	$(BINS) $(LIBS)

binary_file_test: binary_file_test.c $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
