CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=linked_list.o\
float_linked_list.o\

HEADERS=linked_list.h\
float_linked_list.h

LIBS=liblinkedlist.a

BINS=test_float_linked_list\


.phony: clean all

all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

liblinkedlist.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)


test_float_linked_list:	test_float_linked_list.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
