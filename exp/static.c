#include <stdio.h>

// La variable z está definida en el fichero extern.c
// Tenemos que compilar todo junto `gcc static.c extern.c`
// Funciona pero que pasa que si cambiamos en `extern.c` la declaración de z a `static`? Pues que casca y no compila
extern int z;

// ¿Cómo podemos llamar a una función declarada como `static` en otro fichero desde aquí?
// Vamos a verlo usando la función tricky() que está declarada NO COMO static en `extern.c`
void tricky();

void zoo() {
  char b = 3;
  b = b + 1;

  printf("foo: %d\n", b);
}

void bar() {
  // b va retener el valor que tuvo en la última llamada como valor inicial para cada llamada nueva.
  static char b = 3;
  b = b + 1;

  printf("bar: %d\n", b);
}

void main() {

  printf("main: %d\n", z);

  // Primera llamada
  zoo(); // foo: 4
  bar(); // bar: 4

  // Segunda llamada
  zoo(); // foo: 4
  bar(); // bar: 5

  // Tercera llamada
  zoo(); // foo: 4
  bar(); // bar: 6


  // llamando a una función declarada como static en otro fichero
  tricky();
  tricky();

  return;
}