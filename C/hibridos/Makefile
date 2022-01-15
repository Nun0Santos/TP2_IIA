CC=gcc
CFLAGS=-std=c99 -Wpedantic -Wall -Wextra -g
LDFLAGS=-lm -lpthread -lrt

all:
	@$(CC) algoritmo.c funcao.c utils.c main.c $(CFLAGS) $(LDFLAGS) -o output
	@ echo "Compilação realizada com sucesso"

limpa:
	@rm -f *.o output
	@ echo "Foram apagados os ficheiros"