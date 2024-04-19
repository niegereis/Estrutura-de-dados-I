all: pratica.o busca.o
	@gcc pratica.o busca.o -o exe
	@rm -r *.o
pratica.o: pratica.c
	@gcc pratica.c -c -Wall
busca.o: busca.c
	@gcc busca.c -c -Wall
run:
	@./exe
