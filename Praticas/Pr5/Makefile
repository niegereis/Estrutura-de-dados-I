all: pratica.o lista.o
	@gcc pratica.o lista.o -o exe -lm
	@rm -r *.o
lista.o: lista.c
	@gcc lista.c -c -std=c11 -Wall
pratica.o: pratica.c
	@gcc pratica.c -c -std=c11 -Wall
run:
	@./exe
