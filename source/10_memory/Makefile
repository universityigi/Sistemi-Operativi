CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar


BINS=memory_access_test fake_linking fake_mmu_test memory_manager_test

OBJS=linked_list.o fake_mmu.o frame_item.o segment_item.o process_memory_layout.o memory_manager.o

HEADERS=linked_list.h constants_small.h constants_real.h fake_mmu.h frame_item.h segment_item.h process_memory_layout.h memory_manager.h

LIBS=libmemory_manager.a

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

.phony: clean all


all:	$(BINS) $(LIBS)

libmemory_manager.a: $(OBJS) 
	$(AR) -rcs $@ $^
	$(RM) $(OBJS)

memory_access_test: memory_access_test.c
	$(CC) $(CCOPTS) -Ofast -o $@ $^

fake_linking: fake_linking.c
	$(CC) $(CCOPTS) -o $@ $^

fake_mmu_test: fake_mmu_test.c fake_mmu.c 
	$(CC) $(CCOPTS) -D_FAKE_MMU_TEST_ -o $@ $^

memory_manager_test: memory_manager_test.c $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
