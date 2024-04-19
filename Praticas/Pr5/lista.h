#ifndef lista_h
#define lista_h

#include <stdbool.h>

typedef struct {
  char nome[21];
  char matricula[10];
  float coeficiente;
} Aluno;

typedef struct cell {
  Aluno aluno;
  struct cell *prox;
  struct cell *anterior;
} Celula;

typedef struct lista {
  Celula *cabeca;
  Celula *cauda;
  int tamanho;
} Lista;

// Manter como especificado
Lista *ListaInicia();

// Manter como especificado
void ListaLibera(Lista **);

// Manter como especificado
void ListaLe(Lista *, int);

// Manter como especificado
void ListaTroca(Lista *, int, int);

// Manter como especificado
int ListaTamanho(Lista *);

// Manter como especificado
bool ListaInsereNoFinal(Lista *, Aluno);

#endif  // lista_h