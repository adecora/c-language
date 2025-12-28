//#include <stdio.h>

// Podemos chekear si a sólo se carga en regitros, para eso primero tenemos que comentar `stdio.h` y la función `printf`
// Para poder lanzar: `riscv64-unknown-elf-gcc -O0 -S ./register.c`
// Metemos un poco de boilerplate code para que el compilador no se fume esos statements
int main() {

  // Mismo scope que auto, la única diferencia es que le pedimos al compilador que si puede aloje la variable en un registro de la CPU, no es mandatorio
  register int a = 10;
  a = a + 1;
  //printf("main %d\n", a);

  return a;
}