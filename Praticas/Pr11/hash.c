#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Manter como especificado
void inicia(Hash *hash, int qtdAlunos, int qtdPesos) {
  // preencher aqui
  hash->alunos = malloc(sizeof(Aluno) * qtdAlunos);
  hash->pesos = malloc(sizeof(int) * qtdPesos);
  hash->qtdItens = qtdAlunos;
  hash->qtdPesos = qtdPesos;

  for (int i = 0; i < qtdAlunos; i++) {
    hash->alunos[i].matricula = -1;
  }
}

// Manter como especificado
void libera(Hash *hash) {
  free(hash->alunos);
  free(hash->pesos);
}

// Manter como especificado
int H(Hash *hash, Aluno aluno) {
  // preencher aqui
  int matricula = aluno.matricula;
  Nome nome;
  strcpy(nome, aluno.nome);

  unsigned int somatorioNome = 0, somatorioMatricula = 0;
  for (int i = 0; i < strlen(nome); i++) {
    somatorioNome += (unsigned int)nome[i] * hash->pesos[i % hash->qtdPesos];
  }
  int aux = 10000000;
  for (int i = 0; i <= 6; i++) {
    int digitoAtual = (matricula % aux) / (aux / 10);
    aux /= 10;
    somatorioMatricula += (unsigned int)digitoAtual;
  }

  return (somatorioNome + somatorioMatricula) % hash->qtdItens;
}

// Manter como especificado
bool insere(Hash *hash, Aluno aluno) {
  int h = H(hash, aluno);

  int i = h;
  while (hash->alunos[i].matricula != -1 &&
         hash->alunos[i].matricula != aluno.matricula && i < hash->qtdItens) {
    i = (i + 1) % hash->qtdItens;
  }

  if (hash->alunos[i].matricula == -1) {
    hash->alunos[i] = aluno;
    return true;
  }

  return false;
}

// Manter como especificado
void imprime(Hash *hash) {
  for (int i = 0; i < hash->qtdItens; i++) {
    Aluno a = hash->alunos[i];
    printf("[%d] %s - %d (%.1f)\n", a.matricula, a.nome, a.idade, a.peso);
  }
}
//