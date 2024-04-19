#ifndef STACK_H
#define STACK_H

#include "../list/linked-list.h"

typedef LinkedList Stack;

Stack *StackCreate();

bool StackPush(Stack *, Position);
bool StackPop(Stack *, Position *);
bool StackIsEmpty(Stack *stack);
void StackDestroy(Stack **stack);

#endif  // STACK_H