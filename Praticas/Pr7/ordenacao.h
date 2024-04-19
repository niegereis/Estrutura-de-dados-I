#ifndef ORDENACAO_H
#define ORDENACAO_H

typedef struct pacote Pacote;

// Manter como especificado
Pacote *alocaVetor(int);

// Manter como especificado
void lePacotes(Pacote*, int);

// Manter como especificado
void desalocaVetor(Pacote**);

// Manter como especificado
void ordenarPacotes(Pacote*, int);

void imprimirPacotes(Pacote*, int);

#endif // ORDENACAO_H