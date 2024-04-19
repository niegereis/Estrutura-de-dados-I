#include "arranjo.h"

#include <stdio.h>
#include <stdlib.h>

struct arranjo {
  int* v;
  int n;
  int k;
};

// Manter como especificado
void move(Arranjo* pArranjo, int p1, int p2) {
  int valorP2 = pArranjo->v[p2];
  for (int i = p2; i > p1; i--) {
    pArranjo->v[i] = pArranjo->v[i - 1];
  }
  pArranjo->v[p1] = valorP2;
}

// Manter como especificado
void moveBack(Arranjo* pArranjo, int p1, int p2) {
  int valorP1 = pArranjo->v[p1];
  for (int i = p1; i < p2; i++) {
    pArranjo->v[i] = pArranjo->v[i + 1];
  }
  pArranjo->v[p2] = valorP1;
}

// Manter como especificado
void leinfo(int* pN, int* pK) { scanf("%d%d", pN, pK); }

// Manter como especificado
void imprimeArranjo(Arranjo* pArranjo) {
  for (int i = 0; i < pArranjo->k; i++) printf("%d ", pArranjo->v[i]);
  printf("\n");
}

// Manter como especificado
Arranjo* cria(int n, int k) {
  Arranjo* arranjo = (Arranjo*)malloc(sizeof(Arranjo));
  arranjo->v = (int*)malloc(sizeof(int) * n);
  arranjo->k = k;
  arranjo->n = n;
  for (int i = 0; i < arranjo->n; i++) {
    arranjo->v[i] = i + 1;
  }
  return arranjo;
}

// Manter como especificado
void libera(Arranjo** pArranjo) {
  free((*pArranjo)->v);
  free(*pArranjo);
}

// Manter como especificado
void imprime(Arranjo* pArranjo, int index) {
  // PREENCHER AQUI
  if (index == pArranjo->k) {
    imprimeArranjo(pArranjo);
    return;
  }
  for (int i = index; i < pArranjo->n; i++) {
    move(pArranjo, index, i);
    imprime(pArranjo, index + 1);
    moveBack(pArranjo, index, i);
  }
}
