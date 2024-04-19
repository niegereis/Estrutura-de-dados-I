#ifndef arvore_h
#define arvore_h

#include <stdbool.h>
#include <string.h>

typedef char TChave[200];

typedef struct {
  TChave chave;
} TItem;

typedef struct tNo {
  TItem item;
  int vezesNoTxt;
  struct tNo *dir;
  struct tNo *esq;
} TNo;

typedef struct tArvore {
  TNo *pNoRaiz;
} TArvore;

TArvore *TArvoreInicia();
int TArvoreInsere(TArvore *pArvore, TItem item);
TNo *TNoCria(TItem x);
void caminhamento(TNo *p);

#endif
