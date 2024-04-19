#include <stdio.h>
#include <stdlib.h>

#include "ordenacao.h"
int main() {
  int n;
  int i = 0;

  // leia o numero de casos de teste
  scanf("%d", &n);

  // enquanto houver casos de teste
  while (i < n) {
    int p;
    int j;
    // leia o numero de pessoas
    scanf("%d", &p);
    // aloque o vetor
    Pessoa *pessoas = alocaVetor(p);

    // para cada pessoa...
    for (j = 0; j < p; j++) lerPessoa(&(pessoas[j]));

    // use o mergesort para ordenar o vetor
    MergeSort(pessoas, 0, p - 1);

    // imprima o resultado
    printf("Teste %d:\n", i + 1);
    for (j = 0; j < p; j++) {
      imprimePessoa(&(pessoas[j]));
      printf("\n");
    }
    printf("\n");
    // desaloque o vetor
    free(pessoas);
    i++;
  }

  return 0;
}
