#ifndef QUEUE_H
#define QUEUE_H

#include "../list/linked-list.h"
#include "../tree/tree-node.h"

typedef LinkedList Queue;

Queue *QueueCreate();
bool QueuePush(Queue *, Position);
bool QueuePushByNode(Queue *, Node *);
bool QueuePop(Queue *, Position *);
bool QueuePopByNode(Queue *, Node **);
bool QueueIsEmpty(Queue *);
void QueueDestroy(Queue **stack);

#endif  // QUEUE_H