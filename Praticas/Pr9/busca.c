#include "busca.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int* aloca(int n) { return (int*)malloc(sizeof(int) * n); }

void desaloca(int** p) { free(*p); }

void le(int* v, int n) {
  // printf("\nN: %d\n", n);
  for (int i = 0; i < n; i++) {
    // printf("\nI: %d\n", i);
    scanf("%d", &v[i]);
  }
  // printf("Acabou de ler");
}

int buscaSequencial(int* v, int n, int x, int* vezes) {
  for (int i = 0; i < n; i++) {
    (*vezes)++;
    if (v[i] == x) {
      return i;
    }
  }
  return -1;
}

int buscaBinaria(int* v, int n, int x, int* vezes) {
  int direita = n - 1;
  int meio = ((direita) / 2);
  int esquerda = 0;

  while (esquerda <= direita) {
    (*vezes)++;
    if (x == v[meio]) {
      return meio;
    } else if (x > v[meio]) {
      esquerda = (meio + 1);
    } else if (x < v[meio]) {
      direita = meio - 1;
    }
    meio = ((esquerda + direita) / 2);
  }
  return -1;
}

void swap(int* a, int* b) {
  int aux = *a;
  *a = *b;
  *b = aux;
}

int partition(int* v, int p, int r) {
  int pivo = v[r];
  int i = p - 1;
  for (int j = p; j < r; j++) {
    if (v[j] < pivo) {
      i++;
      swap(&(v[i]), &(v[j]));
    }
  }
  swap(&(v[i + 1]), &(v[r]));
  return i + 1;
}

void quick(int* v, int p, int r) {
  if (!(p < r)) return;

  int meio = partition(v, p, r);
  quick(v, p, meio - 1);
  quick(v, meio + 1, r);
}
