CC=gcc
CCOPTS=-std=gnu99
BINS=message_queue_thread_test
LDOPTS=-lrt -lpthread

.phony: clean all

all: $(BINS)

message_queue_thread_test:	message_queue_thread_test.c
	$(CC) -$(CCOPTS) -o $@ $^  $(LDOPTS) 

clean:
	rm -rf *~ $(BINS)

