#include "./find-path.h"

bool FindPathStack(Maze* maze, Path* path) {
  // We initilized-it with -1 to disconsider the initial movement of mouse.
  path->size--;

  Position mousePosition = MazeGetMousePosition(maze);
  Stack* stack = StackCreate();

  StackPush(stack, mousePosition);

  while (!StackIsEmpty(stack)) {
    Position pos;
    bool itemRemoved = StackPop(stack, &pos);

    if (!itemRemoved) break;
    PathAddStep(path, pos);

    if (MazeIsPositionExit(maze, pos)) {
      StackDestroy(&stack);
      return true;
    }

    Queue* availablePositions = MazeGetAvailablePositions(maze, pos, path);
    Position positionAvailable;
    while (QueuePop(availablePositions, &positionAvailable))
      StackPush(stack, positionAvailable);

    LinkedListDestroy(&availablePositions);
  }

  StackDestroy(&stack);

  return false;
}
