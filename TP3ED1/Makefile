# LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro_image

all: linked-list.o queue.o tree.o maze.o position.o path.o tree-node.o main.o
	@gcc ./linked-list.o ./queue.o  \
		./maze.o ./path.o ./position.o  ./tree.o ./tree-node.o\
		 ./main.o  -o exe
	@rm ./linked-list.o
	@rm ./queue.o
	@rm ./position.o
	@rm ./maze.o
	@rm ./path.o
	@rm ./tree.o
	@rm ./main.o
	@rm ./tree-node.o

tree.o: ./tree/tree.c
	@gcc ./tree/tree.c -c -std=c11 -Wall

tree-node.o: ./tree/tree-node.c
	@gcc ./tree/tree-node.c -c -std=c11 -Wall

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

