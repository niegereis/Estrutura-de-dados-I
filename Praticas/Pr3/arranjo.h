#ifndef ARRANJO_H
#define ARRANJO_H

typedef struct arranjo Arranjo;

// Manter como especificado
void leinfo(int*, int*);

// Manter como especificado
Arranjo* cria(int, int);

// Manter como especificado
void libera(Arranjo**);

// Manter como especificado
void imprime(Arranjo*, int);

void move(Arranjo* pArranjo, int p1, int p2);

void moveBack(Arranjo* pArranjo, int p1, int p2);

#endif  // ARRANJO_H