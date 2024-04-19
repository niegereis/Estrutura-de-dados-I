#include "queue.h"

Queue* QueueCreate() {
  Queue* queue = LinkedListCreate();
  return queue;
}

bool QueuePush(Queue* queue, Position position) {
  return LinkedListInsertEnd(queue, position);
}

bool QueuePop(Queue* queue, Position* position) {
  return LinkedListRemoveStart(queue, position);
}

bool QueueIsEmpty(Queue* queue) { return LinkedListIsEmpty(queue); }

void QueueDestroy(Queue** queue) { return LinkedListDestroy(queue); }
