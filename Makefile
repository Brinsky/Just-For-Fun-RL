all: main

main:
	gcc -c *.c
	gcc *.o -o game -lncurses

debug:
	gcc -g -c *.c
	gcc -g *.o -o game -lncurses

clean:
	rm -f *.o game
