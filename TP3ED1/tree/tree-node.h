#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Position position;
  int nivel;
} Item;

typedef struct node {
  Item item;
  struct node* l;
  struct node* r;
  struct node* u;
  struct node* d;
  struct node* father;
} Node;

Node* NodeCreate(Item, Node*);
bool NodeInsertNode(Node**, Item);

#endif  // TREE_NODE_H