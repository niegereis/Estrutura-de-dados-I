
#include <allegro5/allegro.h>

#include "../find-path/find-path.h"
#include "../list/linked-list.h"
#include "../maze/maze.h"
#include "../queue/queue.h"
#include "../stack/stack.h"
#include "../user-interface/user-interface.h"

int main(int argc, char** argv) {
  Maze* maze = MazeCreate();
  MazeRead(maze);

  if (argc >= 2 && strcmp(argv[1], "ui") == 0) {
    UserInterfaceExecute(maze);
  } else {
    Path* path = PathCreate();
    Path* pathPercourred = PathCreate();

    if (maze->option != 'f' && maze->option != 'p' && maze->option != 'r') {
      printf("Opção não conhecida de saida (%c)\n", maze->option);
      printf("Será utilizada a recursão\n");
      maze->option = 'r';
    }

    if (maze->option == 'f') FindPathQueue(maze, pathPercourred);
    if (maze->option == 'p') FindPathStack(maze, pathPercourred);
    bool foundExit;
    if (maze->option == 'r')
      foundExit = FindPathRecursivly(maze, path, pathPercourred);

    if (maze->option == 'r')
      if (foundExit)
        MazePrintWithMarkers(maze, path);
      else
        MazePrintWithMarkers(maze, pathPercourred);
    else
      MazePrintWithMarkers(maze, pathPercourred);

    PathDestroy(&path);
    PathDestroy(&pathPercourred);
    MazeDestroy(&maze);
  }
}
