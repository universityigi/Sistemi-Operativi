CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_
AR=ar

OBJS=functions.o\

HEADERS=functions.h\

LIBS=libautomata.a

BINS=test_function_pointers\

.phony: clean all

all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@ $<

libautomata.a: $(OBJS)
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

test_function_pointers:	test_function_pointers.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
