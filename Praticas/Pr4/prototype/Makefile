all: pratica.o fib.o
	@gcc pratica.o fib.o -o exe
	@rm pratica.o fib.o
praica.o: pratica.c
	@gcc -c pratica.c -Wall
fib.o: fib.c
	@gcc -c fib.c -Wall
run:
	@./exe