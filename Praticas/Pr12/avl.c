#include "avl.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Manter como especificado */
void inicia(No **ppRaiz) { (*ppRaiz) = NULL; }

/* Manter como especificado */
void libera(No **ppRaiz) { free(*ppRaiz); }

/* Manter como especificado */
bool insere(No **ppRaiz, Item x) {
  if (*ppRaiz == NULL) {
    *ppRaiz = criaNo(x);
    return true;
  }
  if (compara((*ppRaiz)->item, x) == MAIOR)
    if (insere(&(*ppRaiz)->pEsq, x)) {
      if (Balanceamento(ppRaiz)) {
        return true;
      } else {
        return false;
      }
    }
  if (compara((*ppRaiz)->item, x) == MENOR)
    if (insere(&(*ppRaiz)->pDir, x)) {
      if (Balanceamento(ppRaiz)) {
        return true;
      } else {
        return false;
      }
    }
  if (compara((*ppRaiz)->item, x) == IGUAL) {
    (*ppRaiz)->cont++;
    return true;
  }

  return false;
}

/* Manter como especificado */
No *criaNo(Item x) {
  No *no = malloc(sizeof(No));
  no->cont = 1;
  no->item = x;
  no->pDir = NULL;
  no->pEsq = NULL;
  return no;
}

/* Manter como especificado */
void caminhamento(No *pNo) {
  if (pNo == NULL) return;

  caminhamento(pNo->pEsq);
  printf("%s %d\n", pNo->item.chave, pNo->cont);
  caminhamento(pNo->pDir);
}

/* Manter como especificado */
RELACAO compara(const Item item1, const Item item2) {
  int response = strcmp(item1.chave, item2.chave);
  if (response < 0)
    return MENOR;
  else if (response > 0)
    return MAIOR;
  return IGUAL;
}

/* Manter como especificado */
int FB(No *pRaiz) {
  if (pRaiz == NULL) return 0;

  return altura(pRaiz->pEsq) - altura(pRaiz->pDir);
}

/* Manter como especificado */
int altura(No *pRaiz) {
  if (pRaiz == NULL) return 0;

  int alturaEsquerda = altura(pRaiz->pEsq);
  int alturaDireita = altura(pRaiz->pDir);

  bool direitaEhMaior = alturaDireita > alturaEsquerda;
  return direitaEhMaior ? alturaDireita + 1 : alturaEsquerda + 1;
}

/* Manter como especificado */
void RSE(No **ppRaiz) {
  No *aux = (*ppRaiz)->pDir;
  (*ppRaiz)->pDir = aux->pEsq;
  aux->pEsq = (*ppRaiz);
  (*ppRaiz) = aux;
}

/* Manter como especificado */
void RSD(No **ppRaiz) {
  No *aux = (*ppRaiz)->pEsq;
  (*ppRaiz)->pEsq = aux->pDir;
  aux->pDir = (*ppRaiz);
  (*ppRaiz) = aux;
}

/* Manter como especificado */
int BalancaEsquerda(No **ppRaiz) {
  int fb = FB((*ppRaiz)->pEsq);
  if (fb >= 0) {
    RSD(ppRaiz);
  } else {
    RSE(&(*ppRaiz)->pEsq);
    RSD(ppRaiz);
  }
  return true;
}

/* Manter como especificado */
int BalancaDireita(No **ppRaiz) {
  int fb = FB((*ppRaiz)->pDir);
  if (fb < 0) {
    RSE(ppRaiz);
  } else {
    RSD(&(*ppRaiz)->pDir);
    RSE(ppRaiz);
  }
  return true;
}

/* Manter como especificado */
int Balanceamento(No **ppRaiz) {
  int fb = FB(*ppRaiz);
  bool desbalanceadaEsquerda = fb > 1;
  bool desbalanceadaDireita = fb < -1;

  if (desbalanceadaEsquerda) return BalancaEsquerda(ppRaiz);
  if (desbalanceadaDireita) return BalancaDireita(ppRaiz);
  return fb;
}
//