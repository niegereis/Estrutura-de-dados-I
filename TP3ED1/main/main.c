#include "../maze/maze.h"
#include "../tree/tree.h"

int main() {
  Path* shortestPath = PathCreate();
  Path* biggestPath = PathCreate();
  Maze* maze = MazeCreate();

  MazeRead(maze);
  Tree* tree = MapMazeRecursivly(maze);

  if (!(TreeMazeFindExit(tree, shortestPath, biggestPath))) {
    printf("EPIC FAIL!\n");
  } else {
    if (maze->option == 'f') imprime(tree->root);

    if (maze->option == 's') MazePrintWithMarkers(maze, shortestPath);

    if (maze->option == 'g') MazePrintWithMarkers(maze, biggestPath);
  }
  return 0;
}