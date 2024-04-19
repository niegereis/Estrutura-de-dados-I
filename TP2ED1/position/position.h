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

#endif  // POSITION_H