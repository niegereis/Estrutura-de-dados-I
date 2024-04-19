#include <stdio.h>
#include <stdlib.h>

#include "busca.h"

int main() {
  int *v, vezes;
  scanf("%d", &vezes);
  for (int i = 0; i < vezes; i++) {
    int n, x;
    scanf("%d", &x);
    scanf("%d", &n);
    v = aloca(n);
    le(v, n);

    int vezesBuscaBin = 0, vezesBuscaSeq = 0;

    buscaSequencial(v, n, x, &vezesBuscaSeq);
    quick(v, 0, n);
    buscaBinaria(v, n, x, &vezesBuscaBin);
    printf("%d %d\n", vezesBuscaSeq, vezesBuscaBin);
    desaloca(&v);
  }
  return 0;
}