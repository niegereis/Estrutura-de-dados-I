#include "turma.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aluno.h"

struct turma {
  Aluno **alunos;    // vetor de ponteiros de alunos
  int tamanhoTurma;  // inteiro com o tamanho da turma
};

// Manter como especificado
void lerInfos(int *qtd, char *option) {
  scanf("%c", option);
  scanf("%d", qtd);
}

// Manter como especificado
Turma *alocaTurma(int qtdAlunos) {
  Turma *turma = (Turma *)malloc(sizeof(Turma));
  turma->alunos = (Aluno **)malloc(sizeof(Aluno *) * qtdAlunos);
  turma->tamanhoTurma = qtdAlunos;
  for (int i = 0; i < qtdAlunos; i++) {
    turma->alunos[i] = alocaAluno();
  }
  return turma;
}

// Manter como especificado
void desalocaTurma(Turma **pTurma) {
  for (int i = 0; i < (*pTurma)->tamanhoTurma; i++) {
    desalocaAluno(&((*pTurma)->alunos[i]));
  }
  free((*pTurma)->alunos);
  free(*pTurma);
}

// Manter como especificado
void lerTurma(Turma *pTurma) {
  for (int i = 0; i < (pTurma)->tamanhoTurma; i++) {
    float nota;
    char nome[30], curso[30];
    scanf(" %s%s%f", nome, curso, &nota);

    atualizarAluno(pTurma->alunos[i], nome, curso, nota);
  }
}

// Manter como especificado
float calcularMetrica(Turma *pTurma, char *curso, char option) {
  float soma = 0;
  int contPessoas = 0;

  for (int i = 0; i < pTurma->tamanhoTurma; i++) {
    float notaAlunoAtual;
    char nomeAlunoAtual[30], cursoAlunoAtual[30];

    infoAluno(pTurma->alunos[i], nomeAlunoAtual, cursoAlunoAtual,
              &notaAlunoAtual);
    if (strcmp(curso, cursoAlunoAtual) == 0) {
      soma += notaAlunoAtual;
      contPessoas++;
    }
  }

  if (option == 'M' && contPessoas > 0) soma /= contPessoas;
  return soma;
}

// Manter como especificado
void printMetrica(char *curso, float metrica, char option) {
  printf("A %s no curso de %s eh %.1f\n", option == 'S' ? "soma" : "media",
         curso, metrica);
}
