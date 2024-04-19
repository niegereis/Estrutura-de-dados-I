all: pratica.o aluno.o turma.o
	@gcc pratica.o aluno.o turma.o -o exe
	@rm -r pratica.o aluno.o turma.o
pratica.o: pratica.c
	@gcc -c pratica.c -Wall
aluno.o: aluno.c
	@gcc -c aluno.c -Wall
turma.o: turma.c
	@gcc -c turma.c -Wall
run:
	@./exe
