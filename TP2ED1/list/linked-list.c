#include "./linked-list.h"

LinkedListNode *LinkedListNodeCreate(Position position) {
  LinkedListNode *linkedListNode = malloc(sizeof(LinkedListNode));

  linkedListNode->position = position;

  return linkedListNode;
}

LinkedList *LinkedListCreate() {
  LinkedList *list = malloc(sizeof(LinkedList));
  list->head = LinkedListNodeCreate(PositionCreate(-1, -1));
  list->tail = LinkedListNodeCreate(PositionCreate(-1, -1));

  list->head->prev = NULL;
  list->tail->next = NULL;

  list->head->next = list->tail;
  list->tail->prev = list->head;

  list->size = 0;

  return list;
}

bool LinkedListIsEmpty(LinkedList *list) {
  return list->head->next == list->tail;
}

bool LinkedListInsertEnd(LinkedList *list, Position position) {
  LinkedListNode *node = LinkedListNodeCreate(position);
  if (node == NULL) return false;

  node->next = list->tail;
  node->prev = list->tail->prev;
  list->tail->prev->next = node;
  list->tail->prev = node;
  list->size++;

  return true;
}

bool LinkedListInsertStart(LinkedList *list, Position position) {
  LinkedListNode *node = LinkedListNodeCreate(position);
  if (node == NULL) return false;
  node->next = list->head->next;
  node->prev = list->head;
  list->head->next->prev = node;
  list->head->next = node;
  list->size++;
  return true;
}

bool LinkedListRemoveEnd(LinkedList *list, Position *position) {
  if (LinkedListIsEmpty(list)) {
    return false;
  }
  LinkedListNode *node;
  node = list->tail->prev;
  list->tail->prev->prev->next = list->tail;
  list->tail->prev = node->prev;
  *position = node->position;
  list->size--;
  free(node);
  return true;
}

bool LinkedListRemoveStart(LinkedList *list, Position *position) {
  if (LinkedListIsEmpty(list)) {
    return false;
  }
  LinkedListNode *node;
  node = list->head->next;
  list->head->next->next->prev = list->head;
  list->head->next = node->next;
  *position = node->position;
  list->size--;
  free(node);
  return true;
}

bool LinkedListHasValue(LinkedList *list, Position position) {
  LinkedListNode *node = list->head->next;
  while (node != list->tail) {
    if (position.x == node->position.x && position.y == node->position.y)
      return true;
    node = node->next;
  }
  return false;
}

void LinkedListDestroy(LinkedList **list) {
  LinkedListNode *node = (*list)->head->next;
  while (node != (*list)->tail) {
    LinkedListNode *next = node->next;
    free(node);
    node = next;
  }
  free((*list)->head);
  free((*list)->tail);
  free(*list);
}

void LinkedListClear(LinkedList *list) {
  LinkedListNode *node = list->head->next;
  while (node != list->tail) {
    LinkedListNode *next = node->next;
    free(node);
    node = next;
  }
  list->size = 0;
  list->head->next = list->tail;
  list->tail->prev = list->head;
}