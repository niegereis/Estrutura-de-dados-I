all: pratica.o ordenacao.o
	@gcc pratica.o ordenacao.o -o exe -lm
	@rm -r pratica.o
	@rm -r ordenacao.o
ordenacao.o: ordenacao.c
	@gcc ordenacao.c -c -Wall
pratica.o: pratica.c
	@gcc pratica.c -c -Wall
run:
	@./exe
