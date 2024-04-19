#ifndef FIND_PATH_H
#define FIND_PATH_H
#include <limits.h>
#include <unistd.h>

#include "../maze/maze.h"
#include "../path/path.h"
#include "../queue/queue.h"
#include "../stack/stack.h"

bool FindPathQueue(Maze* maze, Path* pathPercourred);
bool FindPathStack(Maze* maze, Path* pathPercourred);
bool FindPathRecursivly(Maze* maze, Path* pathFound, Path* pathPercourred);

#endif  // FIND_PATH_H