CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=pool_allocator.o\
     linked_list.o\

HEADERS=linked_list.h  pool_allocator.h

LIBS=libdisastrOS.a

BINS=pool_allocator_test\
     linked_list_test\

#disastros_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

libdisastrOS.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

pool_allocator_test:	pool_allocator_test.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

linked_list_test:	linked_list_test.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
