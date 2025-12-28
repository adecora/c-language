#include <stdio.h>

// Definimos esta variable como global
// int a = 100; // funciona en la llamada a foo y main

// Definimos la variable en otro fichero `extern.c`
// Tenemos que compilar como: `gcc global.c extern.c`
extern int a;

// Para silenciar el compilar cuando movemos foo a otro fichero
//extern void foo();
void foo(); // Tmbn funciona si una función esta declara aunque el compilador no la encuentre en el fichero actual, la acepta y el linker hace el esfuerzo de buscarla en el resto de ficheros
            // Con una variable crashea directamente si no se define el extern.

// Comentamos la función para llevarla a `extern.c`
// void foo() {
//   a = a + 1;
//   printf("foo: %d\n", a);
// }

void main() {
  a = a + 1;
  printf("main: %d\n", a);

  foo(); // Al moverla a `extern.c` ejecuta pero el compilador se queja
         // Silenciamos el error de foo()

  return;
}