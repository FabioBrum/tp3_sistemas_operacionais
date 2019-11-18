CC  = gcc
OBJ = main.o memoria.o utils.o

all: tp3

tp3: $(OBJ)
	$(CC) -o tp3virtual $(OBJ)

utils.o: utils.c utils.h
	$(CC) -c utils.c

memoria.o: memoria.c memoria.h
	$(CC) -c memoria.c
	
main.o: main.c memoria.h utils.h
	$(CC) -c main.c

clean:
	rm *.o
