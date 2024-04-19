#include "./tree.h"

Tree* TreeCreate() {
  Tree* tree = malloc(sizeof(Tree));
  tree->root = NULL;
  return tree;
}

Node* NodeCreate(Item item, Node* father) {
  Node* node = malloc(sizeof(Node));
  node->d = NULL;
  node->l = NULL;
  node->r = NULL;
  node->u = NULL;
  node->father = father;
  node->item = item;
  return node;
}