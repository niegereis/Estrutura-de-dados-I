#ifndef PATH_H
#define PATH_H
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../list/linked-list.h"

typedef struct linkedList Path;

Path* PathCreate();

bool PathAddStep(Path* path, Position position);
bool PathRemoveStep(Path* path, Position* position);
bool PathPercourNext(Path* path, Position* position);
bool PathIsEmpty(Path* path);

void PathCopy(Path* dest, Path* origin);
void PathDestroy(Path** path);

#endif  // PATH_H