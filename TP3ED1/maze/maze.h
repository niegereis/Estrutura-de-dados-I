#ifndef MAZE_H
#define MAZE_H
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../list/linked-list.h"
#include "../path/path.h"
#include "../queue/queue.h"

typedef struct maze {
  char** board;
  int qtyLines;
  int qtyColumns;
  char option;
} Maze;

Maze* MazeCreate();
void MazeRead(Maze* maze);

Position MazeGetMousePosition(Maze* maze);
Queue* MazeGetAvailablePositions(Maze* maze, Position position, Path* path);
bool MazeIsPositionExit(Maze* maze, Position pos);

void MazePrintWithMarkers(Maze* maze, LinkedList* markers);
void MazeDestroy(Maze** maze);

#endif  // MAZE_H