#include <stdio.h>
#include <stdlib.h>

#include "fib.h"

/* colocar o tipo de retorno adequado para grandes numerso */

long long fibonacci(int i, Fib* f) {
  if (i == 0 || i == 1) return i;

  f->calls += 2;

  return fibonacci(i - 1, f) + fibonacci(i - 2, f);
}