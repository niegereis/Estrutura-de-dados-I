#include "./stack.h"

Stack *StackCreate() {
  Stack *stack = LinkedListCreate();
  return stack;
}

bool StackPush(Stack *stack, Position position) {
  return LinkedListInsertStart(stack, position);
}
bool StackPop(Stack *stack, Position *position) {
  return LinkedListRemoveStart(stack, position);
}
bool StackIsEmpty(Stack *stack) { return LinkedListIsEmpty(stack); }

void StackDestroy(Stack **stack) { LinkedListDestroy(stack); }