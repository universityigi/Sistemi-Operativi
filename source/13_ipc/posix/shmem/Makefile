CC=gcc
CCOPTS=-std=gnu99
BINS=shm_writer shm_reader
LDOPTS=-lrt

.phony: clean all

all: $(BINS)

shm_writer:	shm_writer.c
	$(CC) -$(CCOPTS) -o $@ $^  $(LDOPTS) 

shm_reader:	shm_reader.c
	$(CC) -$(CCOPTS) -o $@ $^ $(LDOPTS)

clean:
	rm -rf *~ $(BINS)

