#include "./user-interface.h"

ALLEGRO_DISPLAY *UserInterfaceInit() {
  al_init();
  ALLEGRO_DISPLAY *display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

  al_install_keyboard();
  al_init_primitives_addon();
  al_init_image_addon();
  al_init_font_addon();
  al_init_ttf_addon();
  // al_set_new_display_flags(ALLEGRO_FULLSCREEN);
  // al_set_new_display_refresh_rate(60);
  return display;
}

ALLEGRO_BITMAP *UserInterfaceGetSpriteSheet() {
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
  al_set_new_bitmap_format(ALLEGRO_PIXEL_FORMAT_ANY_16_WITH_ALPHA);
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "assets");
  al_set_path_filename(path, "spritesheet.png");
  ALLEGRO_BITMAP *spriteSheet = al_load_bitmap(al_path_cstr(path, '/'));
  return spriteSheet;
}

ALLEGRO_FONT *UserInterfaceGetFont() {
  ALLEGRO_PATH *path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
  al_append_path_component(path, "assets");
  al_set_path_filename(path, "Daydream.ttf");
  ALLEGRO_FONT *font = al_load_ttf_font(al_path_cstr(path, '/'), 21, 0);
  return font;
}

void UserInterfaceInitializeScenary(Maze *maze, Object **objects, int lines,
                                    int columns) {
  for (int line = 0; line < lines; line++) {
    for (int column = 0; column < columns; column++) {
      if (maze->board[line][column] == 'M' || maze->board[line][column] == ' ')
        objects[line][column] =
            ObjectCreate(column, line, 16 * 2, 0, 16 * 3, 0);
      else
        objects[line][column] =
            ObjectCreate(column, line, 16 * 1, 0, 16 * 2, 16);
    }
  }
}

void UserInterfaceDrawScenary(Object **objects, int lines, int columns,
                              float scaleX, float scaleY) {
  for (int j = 0; j < lines; j++) {
    for (int i = 0; i < columns; i++) {
      Object object = objects[j][i];
      double xPos = (16 * object.position.x) * scaleX;
      double yPos = (16 * object.position.y) * scaleY;

      al_draw_scaled_bitmap(object.sprite,               //
                            0, 0, 16, 16, xPos, yPos,    //
                            16 * scaleX, 16 * scaleY, 0  //
      );
    }
  }
}

void UserInterfaceRun(Maze *maze, Object *mouse, Object **objects,
                      Path *pathPercourred, Path *pathFounded,
                      bool *renderMouse, SearchStrategy searchStrategy,
                      bool *hasEnd) {
  bool isRecursivlyAndIsEmpty =
      searchStrategy == FIND_PATH_BY_RECURSIVLY && PathIsEmpty(pathFounded);
  bool isntRecursivlyAndIsEmpty =
      searchStrategy != FIND_PATH_BY_RECURSIVLY && PathIsEmpty(pathPercourred);
  if (isRecursivlyAndIsEmpty || isntRecursivlyAndIsEmpty) {
    *hasEnd = true;
    *renderMouse = false;
    return;
  }
  Position pos;
  if (!PathIsEmpty(pathPercourred)) {
    if (searchStrategy == FIND_PATH_BY_QUEUE)
      PathPercourNext(pathPercourred, &pos);
    if (searchStrategy == FIND_PATH_BY_STACK)
      PathPercourNext(pathPercourred, &pos);
    if (searchStrategy == FIND_PATH_BY_RECURSIVLY)
      PathRemoveStep(pathFounded, &pos);

    objects[pos.y][pos.x] = ObjectCreate(pos.x, pos.y, 16 * 3, 0, 16 * 4, 0);
  } else {
    *hasEnd = true;
    *renderMouse = false;
  }
  mouse->position = pos;
}

void UserInterfaceShowMenu(ALLEGRO_FONT *font, int selected) {
  al_draw_text(font, al_map_rgb(225, 225, 225), DISPLAY_WIDTH / 2, 20 * SCALE,
               ALLEGRO_ALIGN_CENTRE, "AJUDE O RATO SAIR DO LABIRINTO");

  al_draw_text(font, al_map_rgb(225, 225, 225), DISPLAY_WIDTH / 2, 35 * SCALE,
               ALLEGRO_ALIGN_CENTRE, "selecione o algoritmo");

  al_draw_text(
      font, selected == 0 ? al_map_rgb(0, 0, 220) : al_map_rgb(125, 125, 125),
      DISPLAY_WIDTH / 2, 55 * SCALE, ALLEGRO_ALIGN_CENTRE, "POR PILHA");

  al_draw_text(
      font, selected == 1 ? al_map_rgb(0, 0, 220) : al_map_rgb(125, 125, 125),
      DISPLAY_WIDTH / 2, 70 * SCALE, ALLEGRO_ALIGN_CENTRE, "POR FILA");

  al_draw_text(
      font, selected == 2 ? al_map_rgb(0, 0, 220) : al_map_rgb(125, 125, 125),
      DISPLAY_WIDTH / 2, 85 * SCALE, ALLEGRO_ALIGN_CENTRE, "POR RECURSAO");
}

void UserInterfaceShowPercorredPath(ALLEGRO_FONT *font, int selected) {
  al_draw_text(font, al_map_rgb(225, 225, 225), DISPLAY_WIDTH / 2, 20 * SCALE,
               ALLEGRO_ALIGN_CENTRE,
               "Deseja ver o caminho percorrido pelo rato?");

  al_draw_text(font,
               selected ? al_map_rgb(0, 0, 220) : al_map_rgb(125, 125, 125),
               DISPLAY_WIDTH / 2, 55 * SCALE, ALLEGRO_ALIGN_CENTRE, "SIM");

  al_draw_text(font,
               !selected ? al_map_rgb(0, 0, 220) : al_map_rgb(125, 125, 125),
               DISPLAY_WIDTH / 2, 70 * SCALE, ALLEGRO_ALIGN_CENTRE, "NAO");
}

void UserInterfaceExecute(Maze *maze) {
  ALLEGRO_DISPLAY *display = UserInterfaceInit();
  al_set_target_backbuffer(display);

  ALLEGRO_EVENT_SOURCE *keyboardEventSource = al_get_keyboard_event_source();
  ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
  al_register_event_source(eventQueue, keyboardEventSource);

  double scaleX = ((DISPLAY_WIDTH / (float)maze->qtyColumns) / 16);
  double scaleY = ((DISPLAY_HEIGHT / ((float)maze->qtyLines)) / 16);

  Object **objects = (Object **)malloc(sizeof(Object *) * maze->qtyLines);
  for (int i = 0; i < maze->qtyLines; i++)
    objects[i] = (Object *)malloc(sizeof(Object) * maze->qtyColumns);

  double currentWidth = DISPLAY_WIDTH * scaleX;
  double currentHeight = DISPLAY_HEIGHT * scaleY;

  ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
  al_draw_filled_rectangle(0, 0, currentWidth, currentHeight, white);

  ALLEGRO_FONT *font = UserInterfaceGetFont();

  Path *pathPercourred = PathCreate();
  LinkedList *pathFounded = LinkedListCreate();

  ALLEGRO_EVENT event;
  bool tryAgain = true;
  al_set_new_bitmap_flags(ALLEGRO_NO_PRESERVE_TEXTURE);

  while (tryAgain) {
    UserInterfaceInitializeScenary(maze, objects, maze->qtyLines,
                                   maze->qtyColumns);

    Position mouseInitialPosition = MazeGetMousePosition(maze);
    Object mouse = ObjectCreate(mouseInitialPosition.x, mouseInitialPosition.y,
                                0, 0, 16, 16);
    bool renderMouse = true;
    int selected = 1;
    SearchStrategy searchStrategy = -1;
    al_get_next_event(eventQueue, &event);

    UserInterfaceDrawScenary(objects, maze->qtyLines, maze->qtyColumns, scaleX,
                             scaleY);

    al_draw_filled_rectangle(0, 0, currentWidth, currentHeight,
                             al_map_rgba(50, 50, 50, 220));

    while (searchStrategy == -1) {
      UserInterfaceShowMenu(font, selected);

      if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_S) {
          selected = (selected + 1) % 3;
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_W) {
          selected = (selected - 1);
          if (selected < 0) selected = 2;
        }

        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
          switch (selected) {
            case 0:
              searchStrategy = FIND_PATH_BY_STACK;
              break;
            case 1:
              searchStrategy = FIND_PATH_BY_QUEUE;
              break;
            case 2:
              searchStrategy = FIND_PATH_BY_RECURSIVLY;
              break;
          }
        }
      }

      al_get_next_event(eventQueue, &event);
      al_flip_display();
    }

    UserInterfaceDrawScenary(objects, maze->qtyLines, maze->qtyColumns, scaleX,
                             scaleY);
    al_draw_filled_rectangle(0, 0, currentWidth, currentHeight,
                             al_map_rgba(50, 50, 50, 220));

    if (searchStrategy == FIND_PATH_BY_QUEUE)
      FindPathQueue(maze, pathPercourred);
    if (searchStrategy == FIND_PATH_BY_STACK)
      FindPathStack(maze, pathPercourred);
    if (searchStrategy == FIND_PATH_BY_RECURSIVLY)
      FindPathRecursivly(maze, pathFounded, pathPercourred);

    bool hasEnd = false;
    while (!hasEnd) {
      UserInterfaceRun(maze, &mouse, objects, pathPercourred, pathFounded,
                       &renderMouse, searchStrategy, &hasEnd);
      UserInterfaceDrawScenary(objects, maze->qtyLines, maze->qtyColumns,
                               scaleX, scaleY);

      if (renderMouse)
        al_draw_scaled_bitmap(mouse.sprite, 0, 0, 16, 16,      //
                              mouse.position.x * 16 * scaleX,  //
                              mouse.position.y * 16 * scaleY,  //
                              16 * scaleX, 16 * scaleY, 0);

      /////

      al_get_next_event(eventQueue, &event);
      al_flip_display();
      al_clear_to_color(al_map_rgb(0, 0, 0));
    }

    al_draw_filled_rectangle(0, 0, currentWidth, currentHeight,
                             al_map_rgba(50, 50, 50, 240));
    al_draw_text(font, al_map_rgb(0, 0, 255), DISPLAY_WIDTH / 2,
                 DISPLAY_HEIGHT / 2, ALLEGRO_ALIGN_CENTRE,
                 "O rato ja percorreu o caminho...");
    al_draw_text(font, al_map_rgb(205, 205, 205), DISPLAY_WIDTH / 2,
                 (DISPLAY_HEIGHT / 2) + 75, ALLEGRO_ALIGN_CENTRE,
                 "Digite ENTER para continuar");
    al_draw_text(font, al_map_rgb(205, 205, 205), DISPLAY_WIDTH / 2,
                 (DISPLAY_HEIGHT / 2) + 100, ALLEGRO_ALIGN_CENTRE, "OU");
    al_draw_text(font, al_map_rgb(205, 205, 205), DISPLAY_WIDTH / 2,
                 (DISPLAY_HEIGHT / 2) + 125, ALLEGRO_ALIGN_CENTRE,
                 "ESC para sair!");
    al_flip_display();

    tryAgain = false;
    bool chosed = false;
    while (!chosed) {
      al_get_next_event(eventQueue, &event);
      if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
          tryAgain = false;
          chosed = true;
        } else if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
          chosed = true;
          tryAgain = true;
        }
      }
    }
  }

  // al_destroy_bitmap(mouse);
  // al_destroy_bitmap(mouse);

  // PathDestroy(&pathPercourred);
  // PathDestroy(&pathFounded);

  // for (int i = 0; i < maze->qtyLines; i++) free(objects[i]);
  // free(objects);

  // al_destroy_font(font);

  // al_destroy_user_event_source(keyboardEventSource);
  // al_destroy_event_queue(eventQueue);

  al_destroy_display(display);
}