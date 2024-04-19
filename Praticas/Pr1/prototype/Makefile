all: pratica.o aluno.o
	@gcc pratica.o aluno.o -o exe
pratica.o: pratica.c
		@gcc -c pratica.c -Wall
aluno.o: aluno.c
	@gcc -c aluno.c -Wall
run:
	@./exe
