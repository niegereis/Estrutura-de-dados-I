#include "./object.h"

Object ObjectCreate(int x, int y, int spriteXStart, int spriteYStart,
                    int spriteYEnd, int spriteXEnd) {
  Object object;
  object.position.x = x;
  object.position.y = y;

  ALLEGRO_BITMAP* sprites = UserInterfaceGetSpriteSheet();

  object.sprite = al_create_sub_bitmap(sprites, spriteXStart, spriteYStart,
                                       spriteXEnd, spriteYEnd);

  return object;
}
