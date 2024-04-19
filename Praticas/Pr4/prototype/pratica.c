#include <stdio.h>

#include "fib.h"

int main() {
  // adicionar variaveis conforme a sua necessidade
  Fib f;

  // fazer a leitura do numero de casos de teste dentro do main
  int calls;

  // ler o caso de teste e processar antes de ler o proximo
  scanf("%d", &calls);
  for (int i = 0; i < calls; i++) {
    f.calls = 0;
    int n;
    scanf("%d", &n);
    long long int res;
    res = fibonacci(n, &f);
    printf("fib (%d) = %d chamadas = %lld\n", n, f.calls, res);
  }

  // imprimir a resposta no formato adequado

  return 0;  // nao remova
}