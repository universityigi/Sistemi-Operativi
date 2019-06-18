CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=linked_list.o\

HEADERS=linked_list.h

LIBS=liblinkedlist.a

BINS=linked_list_test\

#disastros_test

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

liblinkedlist.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)


linked_list_test:	linked_list_test.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
