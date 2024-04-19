#include "queue.h"

Queue* QueueCreate() {
  Queue* queue = LinkedListCreate();
  return queue;
}

bool QueuePush(Queue* queue, Position position) {
  return LinkedListInsertEnd(queue, position, NULL);
}

bool QueuePop(Queue* queue, Position* position) {
  return LinkedListRemoveStart(queue, position, NULL);
}

bool QueueIsEmpty(Queue* queue) { return LinkedListIsEmpty(queue); }

void QueueDestroy(Queue** queue) { return LinkedListDestroy(queue); }

bool QueuePushByNode(Queue* queue, struct node* node) {
  return LinkedListInsertEnd(queue, PositionCreate(-1, -1), node);
}
bool QueuePopByNode(Queue* queue, struct node** node) {
  Position p;
  return LinkedListRemoveStart(queue, &p, node);
}
