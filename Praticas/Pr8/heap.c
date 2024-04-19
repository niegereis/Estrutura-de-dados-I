#include "heap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void heapConstroi(Upa*);
void heapRefaz(Upa*, int, int);
void heapInsere(Upa*, Paciente);
bool compara(const Paciente*, const Paciente*);

Upa* alocaUpa(int qtdUpas) {
  Upa* upa = (Upa*)malloc(qtdUpas * sizeof(Upa));
  for (int i = 0; i < qtdUpas; i++) upa[i].qtdPacientes = 0;
  return upa;
}

Paciente* alocaPaciente(int n) {
  Paciente* pacientes;
  pacientes = (Paciente*)malloc(n * sizeof(Paciente));
  return pacientes;
}

void desalocarUpa(Upa** upa) {
  desalocarPacientes(&((*upa)->pacientes));
  free(*upa);
}

void desalocaUpas(Upa* upas, int qtdUpas) {
  for (int i = 0; i < qtdUpas; i++) desalocarPacientes(&(upas[i].pacientes));
  free(upas);
}

void desalocarPacientes(Paciente** pacientes) { free(*pacientes); }

void lePacientesUpa(Upa* upa) {
  for (int i = 0; i < upa->qtdPacientes; i++) {
    Paciente* pacienteAtual = &(upa->pacientes[i]);
    scanf("%s %d %d", pacienteAtual->nome, &(pacienteAtual->idade),
          &pacienteAtual->estado);
  }
  heapConstroi(upa);
}

void agrupaUpas(Upa* upas, int n, Upa* upa) {
  for (int j = 0; j < n; j++)
    for (int k = 0; k < upas[j].qtdPacientes; k++)
      heapInsere(upa, upas[j].pacientes[k]);
}

void imprimeUpa(Upa* upa) {
  for (int i = 0; i < upa->qtdPacientes; i++)
    printf("%s %d %d\n", upa->pacientes[i].nome, upa->pacientes[i].idade,
           upa->pacientes[i].estado);
}

void heapConstroi(Upa* upa) {
  int esquerda = (upa->qtdPacientes / 2) - 1;
  while (esquerda >= 0) {
    heapRefaz(upa, esquerda, upa->qtdPacientes - 1);
    esquerda--;
  }
}

void heapRefaz(Upa* upa, int esq, int dir) {
  int i = esq;
  int j = (i * 2) + 1;

  Paciente auxPaciente = upa->pacientes[i];
  while (j <= dir) {
    if (j < dir && !compara(&upa->pacientes[j], &upa->pacientes[j + 1])) j++;
    if (compara(&auxPaciente, &upa->pacientes[j])) break;

    upa->pacientes[i] = upa->pacientes[j];
    i = j;
    j = i * 2 + 1;
  }

  upa->pacientes[i] = auxPaciente;
}

void heapInsere(Upa* upa, Paciente paciente) {
  upa->pacientes[upa->qtdPacientes] = paciente;
  upa->qtdPacientes++;
  heapConstroi(upa);
}

bool compara(const Paciente* p1, const Paciente* p2) {
  if (p1->estado != p2->estado) return p1->estado > p2->estado;
  if (p1->idade != p2->idade) return p1->idade > p2->idade;

  return strcmp(p1->nome, p2->nome) < 0;
}