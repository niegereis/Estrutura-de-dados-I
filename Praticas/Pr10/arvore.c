#include "arvore.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manter como especificado
TArvore *TArvoreInicia() {
  TArvore *arvore = (TArvore *)malloc(sizeof(TArvore));
  arvore->pNoRaiz = NULL;
  return arvore;
}

int TArvoreInsereR(TNo **no, TItem item);
// Manter como especificado
int TArvoreInsere(TArvore *pArvore, TItem item) {
  if (pArvore->pNoRaiz == NULL) {
    pArvore->pNoRaiz = TNoCria(item);
    return true;
  }

  if (strcmp(item.chave, pArvore->pNoRaiz->item.chave) < 0)
    TArvoreInsereR(&(pArvore->pNoRaiz->esq), item);
  else if (strcmp(item.chave, pArvore->pNoRaiz->item.chave) > 0)
    TArvoreInsereR(&(pArvore->pNoRaiz->dir), item);
  else
    pArvore->pNoRaiz->vezesNoTxt++;
  return 0;
}

int TArvoreInsereR(TNo **no, TItem item) {
  if ((*no) == NULL) {
    *no = TNoCria(item);
    return 1;
  }

  if (strcmp(item.chave, (*no)->item.chave) == 0) {
    (*no)->vezesNoTxt++;
    return 0;
  }

  if (strcmp(item.chave, (*no)->item.chave) < 0)
    return TArvoreInsereR(&(*no)->esq, item);

  else if (strcmp(item.chave, (*no)->item.chave) > 0)
    return TArvoreInsereR(&(*no)->dir, item);

  return 1;
}

// Manter como especificado
TNo *TNoCria(TItem x) {
  TNo *p = (TNo *)malloc(sizeof(TNo));
  p->item = x;
  p->esq = NULL;
  p->dir = NULL;
  p->vezesNoTxt = 1;
  return p;
}

// realizar o caminhamento adequado na arvore
// Manter como especificado
void caminhamento(TNo *p) {
  // PREENCHER AQUI
  if (p == NULL) return;

  caminhamento(p->esq);
  printf("%s %d\n", p->item.chave, p->vezesNoTxt);
  caminhamento(p->dir);
}
