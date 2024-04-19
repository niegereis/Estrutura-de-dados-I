#include "./linked-list.h"

LinkedListNode *LinkedListNodeCreate(Position position) {
  LinkedListNode *linkedListNode = malloc(sizeof(LinkedListNode));

  linkedListNode->position = position;

  return linkedListNode;
}

LinkedListNode *LinkedListNodeCreateByNode(Node *node) {
  LinkedListNode *linkedListNode = malloc(sizeof(LinkedListNode));

  linkedListNode->node = node;

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

bool LinkedListInsertEnd(LinkedList *list, Position position, Node *nodeAux) {
  LinkedListNode *listNode = LinkedListNodeCreate(position);
  if (listNode == NULL) return false;

  listNode->next = list->tail;
  listNode->prev = list->tail->prev;
  list->tail->prev->next = listNode;
  list->tail->prev = listNode;
  list->size++;
  listNode->node = nodeAux;
  return true;
}

bool LinkedListInsertStart(LinkedList *list, Position position, Node *nodeAux) {
  LinkedListNode *listNode = LinkedListNodeCreate(position);
  if (listNode == NULL) return false;
  listNode->next = list->head->next;
  listNode->prev = list->head;
  list->head->next->prev = listNode;
  list->head->next = listNode;
  list->size++;
  listNode->node = nodeAux;
  return true;
}

bool LinkedListRemoveEnd(LinkedList *list, Position *position, Node **nodeAux) {
  if (LinkedListIsEmpty(list)) {
    return false;
  }
  LinkedListNode *listNode;
  listNode = list->tail->prev;
  list->tail->prev->prev->next = list->tail;
  list->tail->prev = listNode->prev;
  *position = listNode->position;
  if (nodeAux != NULL) *nodeAux = listNode->node;
  list->size--;

  free(listNode);
  return true;
}

bool LinkedListRemoveStart(LinkedList *list, Position *position,
                           Node **nodeAux) {
  if (LinkedListIsEmpty(list)) {
    return false;
  }
  LinkedListNode *listNode;
  listNode = list->head->next;
  list->head->next->next->prev = list->head;
  list->head->next = listNode->next;
  *position = listNode->position;
  if (nodeAux != NULL) *nodeAux = listNode->node;
  list->size--;
  free(listNode);
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