#ifndef BUSCA_H
#define BUSCA_H

int* aloca(int);
void desaloca(int**);
void le(int*, int);
int buscaSequencial(int*, int, int, int*);
int buscaBinaria(int*, int, int, int*);

void quick(int* v, int p, int r);

#endif  // BUSCA_H