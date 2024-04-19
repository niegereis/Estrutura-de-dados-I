#include "./path.h"

Path* PathCreate() {
  LinkedList* list = LinkedListCreate();
  return list;
}

bool PathAddStep(Path* path, Position position) {
  return LinkedListInsertEnd(path, position, NULL);
}

bool PathRemoveStep(Path* path, Position* position) {
  return LinkedListRemoveEnd(path, position, NULL);
}

bool PathPercourNext(Path* path, Position* position) {
  return LinkedListRemoveStart(path, position, NULL);
}

bool PathIsEmpty(Path* path) { return LinkedListIsEmpty(path); }

void PathCopy(Path* dest, Path* origin) {
  LinkedListNode* originNode = origin->head->next;
  LinkedListClear(dest);
  while (originNode != origin->tail) {
    LinkedListInsertEnd(dest, originNode->position, NULL);
    originNode = originNode->next;
  }
}

void PathDestroy(Path** path) { LinkedListDestroy(path); }