// cc -o main enum-2.c && ./main
#include <stdio.h>

// Uppercase puede ser recomendado
enum xyz {
  a,
  b,
  c
};


int main() {
  // Puramente cosmetico equivale a int e y puedo almacenar cualquier valore entero
  enum xyz e;
  // La intención que el código sea autodocumentado, that means que usemos enum para almacenar sólo a, b, c los valores del enum.

  e = 10;
  printf("e: %d\n", e);

  int l;

  printf("a: %d\n", a);
  printf("b: %d\n", b);
  printf("c: %d\n", c);

  l = a;

  printf("l: %d\n", l);

  return 0;
}