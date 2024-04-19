#include "./maze.h"

Maze *MazeCreate() {
  Maze *maze = (Maze *)malloc(sizeof(Maze));
  return maze;
}

void MazeDestroy(Maze **maze) {
  for (int i = 0; i < (*maze)->qtyLines; i++) free((*maze)->board[i]);
  free((*maze)->board);
  free(*maze);
}

void MazeRead(Maze *maze) {
  scanf("%d%d", &maze->qtyLines, &maze->qtyColumns);
  scanf(" %c ", &maze->option);

  maze->board = (char **)malloc(maze->qtyLines * (sizeof(char *)));
  for (int i = 0; i < maze->qtyLines; i++) {
    maze->board[i] = (char *)malloc(maze->qtyColumns * (sizeof(char)));
  }
  for (int i = 0; i < maze->qtyLines; i++) {
    for (int j = 0; j < maze->qtyColumns; j++) {
      scanf("%c", &maze->board[i][j]);
    }
    char aux;
    scanf("%c", &aux);
  }
}

void MazePrintWithMarkers(Maze *maze, LinkedList *markers) {
  printf("%d\n", markers->size);
  for (int i = 0; i < maze->qtyLines; i++) {
    for (int j = 0; j < maze->qtyColumns; j++) {
      if (maze->board[i][j] == 'M' ||
          !LinkedListHasValue(markers, PositionCreate(j, i))) {
        printf("%c", maze->board[i][j]);
      } else {
        printf(".");
      }
    }
    printf("\n");
  }
}

bool MazePositionsAvailable(Maze *maze, Position position) {
  bool isInWidth = position.x >= 0 && position.x < maze->qtyColumns;
  bool isInHeight = position.y >= 0 && position.y < maze->qtyLines;
  if (!isInWidth || !isInHeight) return false;

  bool isFree = maze->board[position.y][position.x] == ' ';
  return isFree && isInWidth && isInHeight;
}

Queue *MazeGetAvailablePositions(Maze *maze, Position position,
                                 Path *excludePath) {
  Queue *positions = QueueCreate();

  Position pos = PositionCreate(position.x + 1, position.y);
  bool alreadyPassedHere = LinkedListHasValue(excludePath, pos);
  bool posIsAvailable = MazePositionsAvailable(maze, pos);
  if (posIsAvailable && !alreadyPassedHere) QueuePush(positions, pos);

  pos = PositionCreate(position.x, position.y + 1);
  alreadyPassedHere = LinkedListHasValue(excludePath, pos);
  posIsAvailable = MazePositionsAvailable(maze, pos);
  if (posIsAvailable && !alreadyPassedHere) QueuePush(positions, pos);

  pos = PositionCreate(position.x - 1, position.y);
  alreadyPassedHere = LinkedListHasValue(excludePath, pos);
  posIsAvailable = MazePositionsAvailable(maze, pos);
  if (posIsAvailable && !alreadyPassedHere) QueuePush(positions, pos);

  pos = PositionCreate(position.x, position.y - 1);
  alreadyPassedHere = LinkedListHasValue(excludePath, pos);
  posIsAvailable = MazePositionsAvailable(maze, pos);
  if (posIsAvailable && !alreadyPassedHere) QueuePush(positions, pos);
  return positions;
}

Position MazeGetMousePosition(Maze *maze) {
  for (int i = 0; i < maze->qtyLines; i++) {
    for (int j = 0; j < maze->qtyColumns; j++) {
      if (maze->board[i][j] == 'M') return PositionCreate(j, i);
    }
  }
  return PositionCreate(-1, -1);
}

void DirectionPrint(Direction direction) {
  if (direction == UP) {
    printf("CIMA");
  } else if (direction == DOWN) {
    printf("BAIXO");
  } else if (direction == LEFT) {
    printf("ESQUERDA");
  } else if (direction == RIGHT) {
    printf("DIREITA");
  }
}

bool MazeIsPositionExit(Maze *maze, Position pos) {
  return maze->qtyColumns - 1 == pos.x && maze->qtyLines - 2 == pos.y;
}
