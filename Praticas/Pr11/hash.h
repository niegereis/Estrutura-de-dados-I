#ifndef hash_h
#define hash_h

#include <stdbool.h>

typedef char Nome[51];

typedef struct {
  Nome nome;
  int matricula;
  int idade;
  float peso;
} Aluno;

typedef struct {
  Aluno* alunos;
  int* pesos;
  int qtdPesos;
  int qtdItens;
} Hash;

// Manter como especificado
void inicia(Hash* hash, int qtdItems, int qtdPesos);

// Manter como especificado
void libera(Hash*);

// Manter como especificado
int H(Hash*, Aluno);

// Manter como especificado
bool insere(Hash*, Aluno);

// Manter como especificado
void imprime(Hash*);

#endif
