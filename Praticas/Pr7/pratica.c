#include <stdio.h>

#include "ordenacao.h"

int main() {
  int n;
  Pacote *pacotes;

  // le o numero de pacotes
  scanf("%d", &n);

  // alocar o vetor
  pacotes = alocaVetor(n);
  // le os pacotes
  lePacotes(pacotes, n);

  // ordena os pacotes
  ordenarPacotes(pacotes, n);

  // imprima o resultado
  imprimirPacotes(pacotes, n);

  // desaloque o vetor
  desalocaVetor(&pacotes);
  return 0;
}
