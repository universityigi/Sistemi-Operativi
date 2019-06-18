CC=gcc
CCOPTS=-std=gnu99
BINS=message_sender\
     message_receiver\
     shmem_writer\
     shmem_reader

.phony: clean all

all: $(BINS)

message_sender:	message_sender.c
	$(CC) -$(CCOPTS) -o $@ $^

message_receiver:	message_receiver.c
	$(CC) -$(CCOPTS) -o $@ $^

shmem_writer:	shmem_writer.c
	$(CC) -$(CCOPTS) -o $@ $^

shmem_reader:	shmem_reader.c
	$(CC) -$(CCOPTS) -o $@ $^


clean:
	rm -rf *~ $(BINS)
