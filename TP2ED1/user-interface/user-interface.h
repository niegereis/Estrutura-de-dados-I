#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#include "../find-path/find-path.h"
#include "../list/linked-list.h"
#include "../maze/maze.h"
#include "./object.h"
#define SCALE 5
#define DISPLAY_WIDTH 1280
#define DISPLAY_HEIGHT 720

typedef enum {
  FIND_PATH_BY_QUEUE,
  FIND_PATH_BY_RECURSIVLY,
  FIND_PATH_BY_STACK
} SearchStrategy;

typedef struct {
  int x;
  int y;
} Rato;

typedef struct {
  Rato* rato;
} UserInterface;

// void UserInterfaceInit();
void UserInterfaceExecute(Maze* maze);
ALLEGRO_BITMAP* UserInterfaceGetSpriteSheet();

#endif  // USER_INTERFACE_H