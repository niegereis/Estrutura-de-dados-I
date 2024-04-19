#include "tree.h"

Item ItemCreate(Position position) {
  Item item;
  item.position = position;
  return item;
}

Tree* TreeFromMaze(Maze* maze) {
  Position position = MazeGetMousePosition(maze);
  Tree* tree = TreeCreate();
  Item item = ItemCreate(position);
  NodeInsertNode(&(tree->root), item);

  return tree;
}

bool NodeInsertNode(Node** node, Item item) {
  Node* aux = NodeCreate(item, *node);
  if (*node == NULL) {
    *node = aux;
    return true;
  }
  Direction direction =
      PositionToDirection(item.position, (*node)->item.position);
  switch (direction) {
    case UP:
      (*node)->u = aux;
      break;
    case DOWN:
      (*node)->d = aux;
      break;
    case RIGHT:
      (*node)->r = aux;
      break;
    case LEFT:
      (*node)->l = aux;
      break;
  }
  return true;
}

Node** NodeGetNodeByPositionDirection(Node* currentNode, Position position) {
  Direction direction =
      PositionToDirection(currentNode->item.position, position);

  switch (direction) {
    case UP:
      return &(currentNode->u);
    case DOWN:
      return &(currentNode->d);
    case RIGHT:
      return &(currentNode->r);
    case LEFT:
      return &(currentNode->l);
    default:
      return NULL;
  }
}

void PrintNodesByLevel(Node* root) {
  if (root == NULL) return;

  Queue* queue = QueueCreate();
  QueuePushByNode(queue, root);
  QueuePushByNode(queue, NULL);
  Node* current;
  bool verificar = true;
  int nivel = 1;
  printf("\nNivel %d:\n", nivel++);
  while (QueuePopByNode(queue, &current)) {
    if (queue->head->next->node == NULL) {
      verificar = true;
    }
    if (current == NULL) {
      if (queue->head->next->node != NULL) printf("\nNivel %d:\n", nivel++);
      continue;
    }
    printf(" ");
    PositionPrint(current->item.position);

    if (current->d != NULL) QueuePushByNode(queue, current->d);
    if (current->u != NULL) QueuePushByNode(queue, current->u);
    if (current->r != NULL) QueuePushByNode(queue, current->r);
    if (current->l != NULL) QueuePushByNode(queue, current->l);
    if (verificar) {
      QueuePushByNode(queue, NULL);
      verificar = false;
    }
  }
  printf("\n");
  free(queue);
}

void TreePrintNodesByLevel(Tree* tree) { PrintNodesByLevel(tree->root); }

void MapMaze(Maze* maze, Position pos, Path* currentPath, Node** currentNode,
             Node* fatherNode);

Tree* MapMazeRecursivly(Maze* maze) {
  Path* currentPath = PathCreate();
  Tree* tree = TreeCreate();
  tree->mazeExit = PositionCreate(maze->qtyColumns - 1, maze->qtyLines - 2);
  Position mousePosition = MazeGetMousePosition(maze);
  MapMaze(maze, mousePosition, currentPath, &(tree->root), NULL);
  PathDestroy(&currentPath);
  return tree;
}

void MapMaze(Maze* maze, Position pos, Path* currentPath, Node** currentNode,
             Node* fatherNode) {
  *currentNode = NodeCreate(ItemCreate(pos), fatherNode);
  PathAddStep(currentPath, pos);

  Queue* availablePositions = MazeGetAvailablePositions(maze, pos, currentPath);
  Position availablePosition;
  while (QueuePop(availablePositions, &availablePosition)) {
    Node** auxNode =
        NodeGetNodeByPositionDirection(*currentNode, availablePosition);
    MapMaze(maze, availablePosition, currentPath, auxNode, *currentNode);
    PathRemoveStep(currentPath, &availablePosition);
  }

  LinkedListDestroy(&availablePositions);
}

bool NodeIsLeaf(Node* node) {
  if (node->d == NULL && node->l == NULL && node->r == NULL &&
      node->u == NULL) {
    return true;
  }
  return false;
}

// Função recursiva
void TreeMazeFindExitRecursivly(Position exitMazePosition, Node* node,
                                Path* shortestPath, Path* biggestPath,
                                Path* currentPath) {
  PathAddStep(currentPath, node->item.position);
  if (exitMazePosition.x == node->item.position.x &&
      exitMazePosition.y == node->item.position.y) {
    if (currentPath->size < shortestPath->size) {
      PathCopy(shortestPath, currentPath);
    }
    if (currentPath->size > biggestPath->size) {
      PathCopy(biggestPath, currentPath);
    }
  }
  if (NodeIsLeaf(node)) return;
  Position p;
  if (node->r != NULL) {
    TreeMazeFindExitRecursivly(exitMazePosition, node->r, shortestPath,
                               biggestPath, currentPath);
    PathRemoveStep(currentPath, &p);
  }
  if (node->d != NULL) {
    TreeMazeFindExitRecursivly(exitMazePosition, node->d, shortestPath,
                               biggestPath, currentPath);
    PathRemoveStep(currentPath, &p);
  }
  if (node->l != NULL) {
    TreeMazeFindExitRecursivly(exitMazePosition, node->l, shortestPath,
                               biggestPath, currentPath);
    PathRemoveStep(currentPath, &p);
  }
  if (node->u != NULL) {
    TreeMazeFindExitRecursivly(exitMazePosition, node->u, shortestPath,
                               biggestPath, currentPath);
    PathRemoveStep(currentPath, &p);
  }
}

// Função que chama função recursiva
bool TreeMazeFindExit(Tree* tree, Path* shortestPath, Path* biggestPath) {
  shortestPath->size = INT_MAX;
  biggestPath->size = INT_MIN;

  Path* currentPath = PathCreate();

  TreeMazeFindExitRecursivly(tree->mazeExit, tree->root, shortestPath,
                             biggestPath, currentPath);

  shortestPath->size--;
  biggestPath->size--;

  PathDestroy(&currentPath);

  return (shortestPath->size != INT_MAX - 1);
}

void imprime(Node* root) {
  if (root == NULL) return;

  Queue* queue = QueueCreate();
  QueuePushByNode(queue, root);
  Node* node;
  root->item.nivel = 1;
  int nivelAnterior = root->item.nivel - 1;

  while (QueuePopByNode(queue, &node)) {
    if (node->item.nivel != nivelAnterior) printf("\n%d \n", node->item.nivel);
    PositionPrint(node->item.position);

    if (node->d != NULL) {
      QueuePushByNode(queue, node->d);
      node->d->item.nivel = node->item.nivel + 1;
    }
    if (node->u != NULL) {
      QueuePushByNode(queue, node->u);
      node->u->item.nivel = node->item.nivel + 1;
    }
    if (node->r != NULL) {
      QueuePushByNode(queue, node->r);
      node->r->item.nivel = node->item.nivel + 1;
    }
    if (node->l != NULL) {
      QueuePushByNode(queue, node->l);
      node->l->item.nivel = node->item.nivel + 1;
    }
    nivelAnterior = node->item.nivel;
  }
  printf("\n");
  free(queue);
}

int menorNivelFolha(Node* no, int nivel) {
  if (no == NULL) return 0;

  Queue* queue = QueueCreate();
  QueuePushByNode(queue, no);
  int nivelAnterior = 1;
  Node* current;
  while (QueuePopByNode(queue, current)) {
    if (current->d != NULL) {
      QueuePushByNode(current->d);
      nivelAnterior = nivel + 1;
    }
    if (current->l != NULL) {
      QueuePushByNode(current->l);
      nivelAnterior = nivel + 1;
    }
    if (current->r != NULL) {
      QueuePushByNode(current->r);
      nivelAnterior = nivel + 1;
    }
    if (current->u != NULL) {
      QueuePushByNode(current->u);
      nivelAnterior = nivel + 1;
    }
  }
}