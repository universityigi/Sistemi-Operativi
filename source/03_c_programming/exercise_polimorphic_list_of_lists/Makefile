CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_
AR=ar

OBJS=polimorphic_list.o\
polimorphic_matrix.o\

HEADERS=polimorphic_list.h\
polimorphic_matrix.h\

LIBS=liblinkedlist.a

BINS=test_list_of_lists\

.phony: clean all


all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

liblinkedlist.a: $(OBJS)
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)


test_list_of_lists:	test_list_of_lists.c $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
