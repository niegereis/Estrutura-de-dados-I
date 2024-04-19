#include "./find-path.h"

void FindPath(Maze* maze, Position pos, Stack* currentPath, Path* pathFound,
              Path* pathPercourred);

bool FindPathRecursivly(Maze* maze, Path* pathFound, Path* pathPercourred) {
  Stack* currentPath = PathCreate();
  LinkedListClear(pathFound);
  pathFound->size = INT_MAX;

  Position mousePosition = MazeGetMousePosition(maze);
  FindPath(maze, mousePosition, currentPath, pathFound, pathPercourred);

  bool foundPath = !LinkedListIsEmpty(pathFound);
  if (!foundPath) PathCopy(pathFound, currentPath);

  // We initilized-it with -1 to disconsider the initial movement of mouse.
  currentPath->size--;
  pathFound->size--;
  pathPercourred->size--;

  StackDestroy(&currentPath);

  return foundPath;
}

void FindPath(Maze* maze, Position pos, Stack* currentPath, Path* pathFound,
              Path* pathPercourred) {
  StackPush(currentPath, pos);
  PathAddStep(pathPercourred, pos);
  if (MazeIsPositionExit(maze, pos) && currentPath->size < pathFound->size)
    return PathCopy(pathFound, currentPath);

  Queue* availablePositions = MazeGetAvailablePositions(maze, pos, currentPath);
  Position availablePosition;
  while (QueuePop(availablePositions, &availablePosition)) {
    FindPath(maze, availablePosition, currentPath, pathFound, pathPercourred);
    StackPop(currentPath, &availablePosition);
  }

  LinkedListDestroy(&availablePositions);
}