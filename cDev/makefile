CC=gcc
CFLAGS=-I.
DEPS = structs.h
OBJ = root.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

root: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
