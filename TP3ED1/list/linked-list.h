#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../position/position.h"
#include "../tree/tree-node.h"

typedef struct linkedListNode {
  Position position;
  Node *node;
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
LinkedListNode *LinkedListNodeCreateByNode(Node *);

void LinkedListClear(LinkedList *list);
void LinkedListDestroy(LinkedList **list);

bool LinkedListInsertEnd(LinkedList *, Position, Node *);
bool LinkedListInsertStart(LinkedList *, Position, Node *);

bool LinkedListRemoveEnd(LinkedList *, Position *, Node **);
bool LinkedListRemoveStart(LinkedList *, Position *, Node **);

bool LinkedListIsEmpty(LinkedList *list);
bool LinkedListHasValue(LinkedList *list, Position position);

#endif  // LINKED_LIST_H