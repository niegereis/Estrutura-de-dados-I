#include <stdio.h>

#include "lista.h"

void ListaImprime(Lista *);

int main() {
  int n, p1, p2;
  Lista *lista = ListaInicia();
  scanf("%d", &n);
  ListaLe(lista, n);
  scanf("%d %d", &p1, &p2);
  ListaTroca(lista, p1, p2);
  ListaImprime(lista);
  ListaLibera(&lista);
  return 0;
}

void ListaImprime(Lista *lista) {
  Celula *currentCell = lista->cabeca->prox;
  while (currentCell != lista->cauda) {
    printf("%s %.1f\n", currentCell->aluno.matricula,
           currentCell->aluno.coeficiente);
    currentCell = currentCell->prox;
  }
}
