#ifndef OBJECT_H
#define OBJECT_H

#include <allegro5/allegro5.h>

#include "../position/position.h"
#include "./user-interface.h"

typedef struct {
  Position position;
  ALLEGRO_BITMAP* sprite;
} Object;

Object ObjectCreate(int x, int y, int spriteXStart, int spriteYEnd,
                    int spriteYStart, int spriteXEnd);

#endif  // OBJECT_H