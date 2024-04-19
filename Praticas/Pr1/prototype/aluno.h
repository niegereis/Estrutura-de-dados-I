#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno Aluno;
typedef struct turma Turma;

// Manter como especificado
void lerInfos(int *, char *);

// Manter como especificado
Aluno *alocaAlunos(int);
void desalocaAlunos(Aluno *);

// Manter como especificado
Turma *alocaTurma(int);
void desalocaTurma(Turma **);
void lerTurma(Turma *);
float calcularMetrica(Turma *, char *, char);
void printMetrica(char *, float, char);

#endif  // ALUNO_H