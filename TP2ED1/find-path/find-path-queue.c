#include "./find-path.h"

bool FindPathQueue(Maze* maze, Path* path) {
  // We initilized-it with -1 to disconsider the initial movement of mouse.
  path->size--;

  Position mousePosition = MazeGetMousePosition(maze);
  Queue* queue = QueueCreate();

  QueuePush(queue, mousePosition);

  while (!QueueIsEmpty(queue)) {
    Position pos;
    bool itemRemoved = QueuePop(queue, &pos);

    if (!itemRemoved) break;
    PathAddStep(path, pos);

    if (MazeIsPositionExit(maze, pos)) {
      QueueDestroy(&queue);
      return true;
    }

    Queue* availablePositions = MazeGetAvailablePositions(maze, pos, path);
    Position availablePosition;
    while (QueuePop(availablePositions, &availablePosition))
      QueuePush(queue, availablePosition);

    LinkedListDestroy(&availablePositions);
  }

  QueueDestroy(&queue);

  return false;
}