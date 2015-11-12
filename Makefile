CFLAGS = -Wall -std=c99

all: main

main:
	gcc $(CFLAGS) -c *.c
	gcc $(CFLAGS) *.o -o game -lncurses

debug:
	gcc $(CFLAGS) -g -c *.c
	gcc $(CFLAGS) -g *.o -o game -lncurses

clean:
	rm -f *.o game
