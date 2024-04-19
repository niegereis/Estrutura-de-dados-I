LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image

all: linked-list.o queue.o stack.o find-path.o maze.o position.o path.o user-interface.o main.o
	@gcc ./linked-list.o ./queue.o ./stack.o \
		./find-path-queue.o ./find-path-stack.o ./find-path-recursivly.o \
		./maze.o ./path.o ./position.o ./user-interface.o	 \
		./object.o ./main.o $(LIBS) -o exe
	@rm ./linked-list.o
	@rm ./queue.o
	@rm ./position.o
	@rm ./stack.o
	@rm ./find-path-queue.o
	@rm ./find-path-recursivly.o
	@rm ./find-path-stack.o
	@rm ./maze.o
	@rm ./path.o
	@rm ./object.o
	@rm ./user-interface.o
	@rm ./main.o

linked-list.o: ./list/linked-list.c
	@gcc ./list/linked-list.c -c  -std=c11 -Wall
	
queue.o: ./queue/queue.c
	@gcc ./queue/queue.c -c -std=c11 -Wall

stack.o: ./stack/stack.c
	@gcc ./stack/stack.c -c -std=c11 -Wall

find-path.o: ./find-path/find-path-queue.c ./find-path/find-path-stack.c ./find-path/find-path-recursivly.c
	@gcc ./find-path/find-path-queue.c ./find-path/find-path-stack.c ./find-path/find-path-recursivly.c -c -std=c11 -Wall

maze.o: ./maze/maze.c
	@gcc ./maze/maze.c -c -std=c11 -Wall

path.o: ./path/path.c
	@gcc ./path/path.c -c -std=c11 -Wall

position.o: ./position/position.c
	@gcc ./position/position.c -c -std=c11 -Wall

user-interface.o: ./user-interface/user-interface.c ./user-interface/object.c
	@gcc ./user-interface/user-interface.c ./user-interface/object.c -c -std=c11 -Wall

main.o: ./main/main.c
	@gcc  ./main/main.c -c -std=c11 -Wall

run:
	@./exe