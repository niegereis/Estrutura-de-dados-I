#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main() {
  Hash hash;
  // le tamanho da hash e a quantidade de pesos
  int tamanhoHash;
  int qtdPesos;

  // inicia hash
  scanf("%d %d", &tamanhoHash, &qtdPesos);
  inicia(&hash, tamanhoHash, qtdPesos);

  // le os pesos
  for (int i = 0; i < qtdPesos; i++) {
    scanf("%d", &(hash.pesos[i]));
  }
  // le alunos e ja insere
  Aluno aluno;
  for (int i = 0; i < tamanhoHash; i++) {
    scanf("%s %d %d %f", aluno.nome, &aluno.matricula, &aluno.idade,
          &aluno.peso);
    insere(&hash, aluno);
  }
  // imprime resposta
  imprime(&hash);
  // libera hash
  libera(&hash);
  return 0;
}