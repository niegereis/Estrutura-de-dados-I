#ifndef FIB_H
#define FIB_H

typedef struct {
  int calls;
} Fib;

/* colocar o tipo de retorno adequado para grandes numeros */
long long int fibonacci(int, Fib*);

#endif  // FIB_H