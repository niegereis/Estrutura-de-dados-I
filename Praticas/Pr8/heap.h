#ifndef HEAP_H
#define HEAP_H

typedef struct {
  char nome[50];
  int idade;
  int estado;
} Paciente;

typedef struct {
  Paciente* pacientes;
  int qtdPacientes;
} Upa;

Upa* alocaUpa(int);
void desalocarUpa(Upa**);
void desalocaUpas(Upa*, int);
void desalocarPacientes(Paciente**);
void lePacientesUpa(Upa*);
void agrupaUpas(Upa*, int, Upa*);
void imprimeUpa(Upa*);
Paciente* alocaPaciente(int);

#endif  // HEAP_H