all: pratica.o arvore.o
	@gcc pratica.o arvore.o -o exe -lm
arvore.o: arvore.c
	@gcc arvore.c -c -Wall
pratica.o: pratica.c
	@gcc pratica.c -c -Wall
run:
	@./exe
