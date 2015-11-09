all: main

main:
	gcc -Wall -c *.c
	gcc -Wall *.o -o game -lncurses

debug:
	gcc -Wall -g -c *.c
	gcc -Wall -g *.o -o game -lncurses

clean:
	rm -f *.o game
