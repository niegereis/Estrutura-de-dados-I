#ifndef QUEUE_H
#define QUEUE_H

#include "../list/linked-list.h"

typedef LinkedList Queue;

Queue *QueueCreate();
bool QueuePush(Queue *, Position);
bool QueuePop(Queue *, Position *);
bool QueueIsEmpty(Queue *);
void QueueDestroy(Queue **stack);

#endif  // QUEUE_H