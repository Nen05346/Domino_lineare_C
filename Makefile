# makefile to compile domino's game
CC = gcc

all: build/domino

build/domino: build/domino.o build/main.o
	 $(CC) -o build/domino build/main.o build/domino.o

build/main.o: tools/main.c include/domino.h
	$(CC) -c tools/main.c -o build/main.o -I include

build/domino.o: src/domino.c include/domino.h 
	$(CC) -c src/domino.c -o build/domino.o -I include

clean:
	rm -rf build/*.o build/domino
