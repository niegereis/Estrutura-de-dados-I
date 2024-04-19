#include "./position.h"

Position PositionCreate(int x, int y) {
  Position position;
  position.x = x;
  position.y = y;
  return position;
}

char* PositionToString(Position* position) {
  char* str = malloc(sizeof(char) * 11);
  snprintf(str, 11, "(%d, %d)", position->x, position->y);
  return str;
}

Direction PositionToDirection(Position position, Position origin) {
  if (origin.x == position.x + 1) {
    return RIGHT;
  } else if (origin.x == position.x - 1) {
    return LEFT;
  } else if (origin.y == position.y - 1) {
    return UP;
  } else if (origin.y == position.y + 1) {
    return DOWN;
  }
  return -1;
}

void PositionPrint(Position position) {
  printf("(%d, %d)", position.y, position.x);
}