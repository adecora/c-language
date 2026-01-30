#include <stdio.h>

int main() {
  int a = 5;
  int b = 3;

  printf("a = %d\n", a);
  printf("b = %d\n", b);

  // Remember estas vainas no son a nivel de bit es valor != 0 vs. valor == 0
  printf("\na && b = %d\n", a && b);
  printf("a || b = %d\n", a || b);
  printf("!a = %d\n", a || b);

  a = 0;
  b = 12;

  printf("\na = %d\n", a);
  printf("b = %d\n", b);

  printf("\na && b = %d\n", a && b);
  printf("a || b = %d\n", a || b);
  printf("!a = %d\n", a || b);

  a = -5;
  b = 12;

  printf("\na = %d\n", a);
  printf("b = %d\n", b);

  // Incluso si el valor es negativo estamos en la misma vaina no más evalua != 0 vs. == 0
  printf("\na && b = %d\n", a && b);
  printf("a || b = %d\n", a || b);
  printf("!a = %d\n", a || b);

  return 0;
}