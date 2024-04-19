#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../position/position.h"

typedef struct linkedListNode {
  Position position;
  struct linkedListNode *next;
  struct linkedListNode *prev;
} LinkedListNode;

typedef struct linkedList {
  struct linkedListNode *head;
  struct linkedListNode *tail;
  int size;
} LinkedList;

LinkedList *LinkedListCreate();
LinkedListNode *LinkedListNodeCreate(Position position);

void LinkedListClear(LinkedList *list);
void LinkedListDestroy(LinkedList **list);

bool LinkedListInsertEnd(LinkedList *, Position);
bool LinkedListInsertStart(LinkedList *, Position);

bool LinkedListRemoveEnd(LinkedList *, Position *);
bool LinkedListRemoveStart(LinkedList *, Position *);

bool LinkedListIsEmpty(LinkedList *list);
bool LinkedListHasValue(LinkedList *list, Position position);

#endif  // LINKED_LIST_H