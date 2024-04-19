#include "./path.h"

Path* PathCreate() {
  LinkedList* list = LinkedListCreate();
  return list;
}

bool PathAddStep(Path* path, Position position) {
  return LinkedListInsertEnd(path, position);
}

bool PathRemoveStep(Path* path, Position* position) {
  return LinkedListRemoveEnd(path, position);
}

bool PathPercourNext(Path* path, Position* position) {
  return LinkedListRemoveStart(path, position);
}

bool PathIsEmpty(Path* path) { return LinkedListIsEmpty(path); }

void PathCopy(Path* dest, Path* origin) {
  LinkedListNode* originNode = origin->head->next;
  LinkedListClear(dest);
  while (originNode != origin->tail) {
    LinkedListInsertEnd(dest, originNode->position);
    originNode = originNode->next;
  }
}

void PathDestroy(Path** path) { LinkedListDestroy(path); }