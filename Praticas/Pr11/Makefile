all: pratica.o hash.o
	@gcc pratica.o hash.o -o exe
	@rm -f pratica.o hash.o
pratica.o: pratica.c
		@gcc pratica.c -c
hash.o: hash.c
	@gcc hash.c -c
run:
	@./exe
