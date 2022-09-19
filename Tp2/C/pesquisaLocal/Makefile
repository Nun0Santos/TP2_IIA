CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wextra -g
LDFLAGS=-lm -lpthread -lrt

all:
	@$(CC) algoritmo.c funcao.c utils.c main.c $(CFLAGS) $(LDFLAGS) -o output
	@ echo "Compilation finished sucessfully."

clean:
	@rm -f *.o output
	@ echo "Directory cleaned."