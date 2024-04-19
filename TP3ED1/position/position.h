#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct position {
  int x;
  int y;
} Position;
typedef enum { UP, DOWN, LEFT, RIGHT } Direction;
Position PositionCreate(int x, int y);
void PositionPrint(Position position);
Direction PositionToDirection(Position position, Position origin);

#endif  // POSITION_H