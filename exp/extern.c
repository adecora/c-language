#include <stdio.h>

int a = 500;

int z = 600; // Se lee en `static.c` como `extern` cuando la declaramos global funciona correctamente
// static int z = 600; // Cuando modificamos la declaración a static esta vaina deja de compilar
// Nos dice OJO no reconozco la variable z dentro del main, pues está declaración solo vive en este fichero como `static` y no se lleva a `static.c`
// usr/bin/ld: /tmp/ccAzTmKA.o: warning: relocation against `z' in read-only section `.text'
// /usr/bin/ld: /tmp/ccAzTmKA.o: in function `main':

// Tmbn podemos declarar la función `foo` como `static`, entonces tampoco se podrá usar fuera de este fichero
void foo() {
  a = a + 1;
  printf("foo: %d\n", a);
}

static void zorro() {
  a = a + 1;
  printf("zorro: %d\n", a);
}

void tricky() {
  static int a = 1;
  a = a + 1;

  // Aquí está el trick, aunque zorro está declarada como `static` no se puede llamar desde fuera de este fichero
  // Nosotros la estamos llamando desde dentro del fichero
  // Y lo que incomos en `static.c` es la función `tricky`
  zorro();

  printf("tricky: %d\n", a);
}

