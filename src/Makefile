CC=gcc
CFLAGS=-I.
DEPS = card.h deck.h hand.h
OBJ = card.o tester.o deck.o hand.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

tester: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	/bin/rm -f *.o tester core.* vgcore.*
