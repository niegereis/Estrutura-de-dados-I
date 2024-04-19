#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

int main() {
  int qtdUpas, qtdPacientesTotal = 0;
  scanf("%d", &qtdUpas);
  Upa* upas = alocaUpa(qtdUpas);

  for (int i = 0; i < qtdUpas; i++) {
    scanf("%d", &upas[i].qtdPacientes);

    upas[i].pacientes = alocaPaciente(upas[i].qtdPacientes);
    lePacientesUpa(&upas[i]);

    qtdPacientesTotal = upas[i].qtdPacientes + qtdPacientesTotal;
  }

  Upa* upaAtual = alocaUpa(1);
  upaAtual->pacientes = alocaPaciente(qtdPacientesTotal);

  agrupaUpas(upas, qtdUpas, upaAtual);
  imprimeUpa(upaAtual);

  desalocaUpas(upas, qtdUpas);
  desalocarUpa(&upaAtual);
  return 0;
}