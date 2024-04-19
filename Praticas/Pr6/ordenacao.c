#include "ordenacao.h"

#include <stdio.h>

#include "stdlib.h"
#include "string.h"

void copiaVetor(Pessoa *dest, Pessoa *origin, int size, int offSet);

// Manter como especificado
Pessoa *alocaVetor(int n) {
  Pessoa *pessoas = malloc(n * sizeof(Pessoa));
  return pessoas;
}

// Manter como especificado
void desalocaVetor(Pessoa **vetor) {
  free(*vetor);
  return;
}

// implemente sua funcao do mergesort, que deve invocar a funcao merge
void MergeSort(Pessoa *vetor, int esquerda, int direita) {
  if (!(esquerda < direita)) return;

  int meio = (esquerda + direita) / 2;
  MergeSort(vetor, esquerda, meio);
  MergeSort(vetor, meio + 1, direita);
  merge(vetor, esquerda, meio, direita);
}

// implemente sua funcao do mergesort, que deve invocar a funcao merge
void merge(Pessoa *vetor, int esquerda, int meio, int direita) {
  int sizeL = ((meio - esquerda + 1));
  int sizeR = (direita - meio);

  Pessoa *pessoasEsquerda = alocaVetor(sizeL);
  Pessoa *pessoasDireita = alocaVetor(sizeR);

  copiaVetor(pessoasEsquerda, vetor, sizeL, esquerda);
  copiaVetor(pessoasDireita, vetor, sizeR, meio + 1);

  int i = 0, j = 0;
  for (int k = esquerda; k <= direita; k++) {
    if (i == sizeL) {
      vetor[k] = pessoasDireita[j++];
    } else if (j == sizeR) {
      vetor[k] = pessoasEsquerda[i++];
    } else if (strcmp(pessoasEsquerda[i].name, pessoasDireita[j].name) == 0) {
      if (pessoasEsquerda[i].idade < pessoasDireita[j].idade) {
        vetor[k] = pessoasEsquerda[i++];
      } else {
        vetor[k] = pessoasDireita[j++];
      }
    } else if (strcmp(pessoasEsquerda[i].name, pessoasDireita[j].name) > 0) {
      vetor[k] = pessoasDireita[j++];
    } else {
      vetor[k] = pessoasEsquerda[i++];
    }
  }
}

void copiaVetor(Pessoa *dest, Pessoa *origin, int size, int offSet) {
  for (int i = 0; i < size; i++) {
    dest[i] = origin[i + offSet];
  }
}

void lerPessoa(Pessoa *pessoa) {
  scanf("%s", pessoa->name);
  scanf("%d", &pessoa->idade);
}

void imprimePessoa(Pessoa *pessoa) {
  printf("%s %d", pessoa->name, pessoa->idade);
}