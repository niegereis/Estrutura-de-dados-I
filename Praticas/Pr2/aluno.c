#include "aluno.h"

#include <stdlib.h>
#include <string.h>

struct aluno {
  char* nome;   // nome
  char* curso;  // curso
  float nota;   // nota
};

Aluno* alocaAluno() {
  Aluno* aluno = (Aluno*)malloc(sizeof(Aluno));
  aluno->nome = (char*)malloc(sizeof(char) * 30);
  aluno->curso = (char*)malloc(sizeof(char) * 30);
  return aluno;
}

// Manter como especificado
void desalocaAluno(Aluno** pAluno) {
  free((*pAluno)->curso);
  free((*pAluno)->nome);
  free(*pAluno);
}

void atualizarAluno(Aluno* pAluno, char* nome, char* curso, float nota) {
  strcpy(pAluno->nome, nome);
  strcpy(pAluno->curso, curso);
  pAluno->nota = nota;
}

void infoAluno(Aluno* pAluno, char* nome, char* curso, float* nota) {
  strcpy(nome, pAluno->nome);
  strcpy(curso, pAluno->curso);
  *nota = pAluno->nota;
}
