#include "aluno.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno {
  char nome[63];
  char curso[31];
  float nota;
};

struct turma {
  Aluno *alunos;
  int quantidadeDeAlunos;
};

void lerInfos(int *qtd, char *option) { scanf("%c %d", option, qtd); }

// Manter como especificado
Aluno *alocaAlunos(int qtdAlunos) {
  Aluno *aluno = (Aluno *)malloc(sizeof(Aluno) * qtdAlunos);
  return aluno;
}

// Manter como especificado
Turma *alocaTurma(int qtdAlunos) {
  Turma *turma = (Turma *)malloc(sizeof(Turma));

  turma->quantidadeDeAlunos = qtdAlunos;
  turma->alunos = alocaAlunos(qtdAlunos);

  return turma;
}

// Manter como especificado
void desalocaAlunos(Aluno *pAluno) { free(pAluno); }

// Manter como especificado
void desalocaTurma(Turma **pTurma) {
  desalocaAlunos(((*pTurma)->alunos));
  free(*pTurma);
}

// Manter como especificado
void lerTurma(Turma *pTurma) {
  for (int i = 0; i < pTurma->quantidadeDeAlunos; i++) {
    scanf("%s", pTurma->alunos[i].nome);
    scanf("%s", pTurma->alunos[i].curso);
    scanf("%f", &(pTurma->alunos[i].nota));
  }
}

// Manter como especificado
float calcularMetrica(Turma *pTurma, char *curso, char option) {
  float soma = 0;
  int contPessoas = 0;

  for (int i = 0; i < pTurma->quantidadeDeAlunos; i++) {
    Aluno alunoAtual = pTurma->alunos[i];
    if (strcmp(curso, alunoAtual.curso) == 0) {
      soma += alunoAtual.nota;
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
