#include <stdio.h>

#include "arranjo.h"
int main() {
  int n, k;
  Arranjo* pArranjo;
  leinfo(&n, &k);
  pArranjo = cria(n, k);
  imprime(pArranjo, 0);
  libera(&pArranjo);

  return 0;
}