#ifndef TREE_H
#define TREE_H
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../maze/maze.h"
#include "../position/position.h"
#include "tree-node.h"

typedef struct {
  Node* root;
  Position mazeExit;
} Tree;

Tree* TreeCreate();

void TreePrintNodesByLevel(Tree* tree);
void imprime(Node* root);
Tree* MapMazeRecursivly(Maze* maze);
void PrintNodesByLevel(Node* root);
bool TreeMazeFindExit(Tree* tree, Path* shortestPath, Path* biggestPath);

#endif  // TREE_H