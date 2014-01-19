IDIR = ../include
CC = gcc
CFLAGS = -I$(IDIR) -g

_DEPS = hw1.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))

OBJ = hw1.o functions.o

hw1: $(OBJ)
	$(CC) $^ -o $@

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean: 
	rm -f ./*.o hw1 
