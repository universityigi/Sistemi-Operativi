CC=gcc
CCOPTS=--std=gnu99 -Wall -D_LIST_DEBUG_ 
AR=ar

OBJS=pool_allocator.o\
polimorphic_list.o\

HEADERS=pool_allocator.h\
polimorphic_list.h\
polimorphic_list_types.h

LIBS=libexpoolalloc.a

BINS=test_pool_allocator test_slab_allocator_list

.phony: clean all

all:	$(LIBS) $(BINS)

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

libexpoolalloc.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

test_pool_allocator: test_pool_allocator.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ 

test_slab_allocator_list: test_slab_allocator_list.o $(LIBS)
	$(CC) $(CCOPTS) -o $@ $^ 

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
