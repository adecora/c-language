#include <stdio.h>

void main() {
  {
    // Cuando definimos como `auto` vive en el bloque de código donde se ha definido, en este caso el scope es sólo dentro de los {}
    auto int a = 10;
  }

  printf("%d\n", a); // falla porque a no se ha definido en este scope

  return;
}