CC=gcc
CFLAGS=-I.
DEPS = card.h deck.h hand.h heads_up_holdem.h
OBJ = card.o tester.o deck.o hand.o heads_up_holdem.o

%.o: %.c $(DEPS)
		$(CC) -c -o $@ $< $(CFLAGS)

tester: $(OBJ)
		$(CC) -o $@ $^ $(CFLAGS)

clean:
	/bin/rm -f *.o tester heads_up_holdem core.* vgcore.*
