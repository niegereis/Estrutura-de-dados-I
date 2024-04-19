#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

Lista *ListaInicia() {
  Lista *lista = (Lista *)malloc(sizeof(Lista));

  lista->cabeca = (Celula *)malloc(sizeof(Celula));
  lista->cauda = (Celula *)malloc(sizeof(Celula));

  lista->cabeca->prox = lista->cauda;
  lista->cauda->anterior = lista->cabeca;

  lista->tamanho = 0;

  return lista;
}

void LiberaCelulaRecursiva(Celula *celula) {
  if (celula->anterior == NULL) return;
  Celula *anterior = celula->anterior;
  free(celula);
  LiberaCelulaRecursiva(anterior);
}

void ListaLibera(Lista **ppLista) {
  Celula *atual = (*ppLista)->cabeca;
  while (atual != NULL) {
    Celula *prox = atual->prox;
    free(atual);
    atual = prox;
  }
}

Celula *pegaCelulaPelaPosicao(Lista *lista, int pos) {
  if (pos > lista->tamanho) return NULL;
  Celula *currentCel = lista->cabeca;
  for (int i = 0; i < pos; i++) currentCel = currentCel->prox;
  return currentCel;
}

void ListaTroca(Lista *lista, int p1, int p2) {
  if (p1 == p2) return;
  if (p1 > p2) {
    int aux = p1;
    p1 = p2;
    p2 = aux;
  }
  if (p2 > lista->tamanho + 1 || p1 > lista->tamanho + 1 || p1 < 0 || p2 < 0)
    return;
  Celula *cel1 = pegaCelulaPelaPosicao(lista, p1);
  Celula *proxCel1 = cel1->prox;
  Celula *anteriorCel1 = cel1->anterior;

  Celula *cel2 = pegaCelulaPelaPosicao(lista, p2);
  Celula *proxCel2 = cel2->prox;
  Celula *anteriorCel2 = cel2->anterior;

  anteriorCel1->prox = cel2;
  cel2->prox = proxCel1;
  anteriorCel2->prox = cel1;
  cel1->prox = proxCel2;
  if (p2 - p1 == 1) {
    cel2->prox = cel1;
  }

  cel2->anterior = anteriorCel1;
  proxCel1->anterior = cel2;
  cel1->anterior = anteriorCel2;
  proxCel2->anterior = cel1;
  if (p2 - p1 == 1) {
    cel1->anterior = cel2;
    cel2->anterior = anteriorCel1;
  }
}

void ListaLe(Lista *pLista, int n) {
  Aluno aluno;
  for (int i = 0; i < n; i++) {
    scanf("%s %f %s", aluno.nome, &aluno.coeficiente, aluno.matricula);
    ListaInsereNoFinal(pLista, aluno);
  }
}

int ListaTamanho(Lista *pLista) { return pLista->tamanho; }

bool ListaInsereNoFinal(Lista *pLista, Aluno aluno) {
  Celula *novaCelula = (Celula *)malloc(sizeof(Celula));
  if (novaCelula == NULL) return false;

  novaCelula->aluno = aluno;

  novaCelula->prox = pLista->cauda;
  novaCelula->anterior = pLista->cauda->anterior;
  pLista->cauda->anterior->prox = novaCelula;
  pLista->cauda->anterior = novaCelula;

  pLista->tamanho++;

  return true;
}