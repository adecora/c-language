// Vamos a compilar con `gcc -g strings.c` al usar `-g` el compilador añade mierdas extra al binario generado
// para poder debbugearlo con `gdb a.out`
// break main <= punto de ruptura al empezar el programa
// r  <= run para lanzar el programa
// Los registros que vemos son de maquina Intel de codespace de GitHub
// n <= next para movernos al siguiente statement, OJO la vaina ni next instruccion se mueve instrucción a instrucción del assembly; n next instrucción a instrucción de C
// Podemos ver una vaina así en Variables: loc var1 = <optimized out>, var = 0x555555556032 "Hi": 72 'H'
// básicamente esto dice la dirección de var 0x555555556032, no dice que es un puntero a 72 'H' y que después le siguen más caracteres "Hi" por lo que tiene que ser un string
// p var <= print imprime el valor de var
//    >>> p var
//    $1 = 0x555555556032 "Hi"
//    >>> p var[0]
//    $2 = 72 'H'
//    >>> p var[1]
//    $3 = 105 'i'
//    >>> p var[2]
//    $4 = 0 '\000'  // Remembering la cadenas de caracteres en C tiene que terminar con el caracter nulo '\0'
//
//    // &var para acceder a la dirección de memoria OBVIO son direcciones contiguas 0x555555556032 .. 0x555555556033 .. 0x555555556034
//    >>> p &var[0]
//    6 = 0x555555556032 "Hi"
//    >>> p &var[1]
//    $7 = 0x555555556033 "i"
//    >>> p &var[2]
//    $8 = 0x555555556034 ""
//    ¿Por qué esta vaina empieza indexando por zero? -> La razón tiene que ver con "pointer arithmetic" proximamente...

#include <stdio.h>

int main() {

  char var1;
  printf("The size of «char var1;» is %ld bytes.\n", sizeof(var1));

  char *var = "Hi";
  printf("The size of «char *var;» is %ld bytes.\n", sizeof(var)); // 8 bytes, tiene sentido porque nuestra máquina es x64 bit
                                // 8 bytes * 8 bit/bytes = 64bit para poder redireccionar todas las vainas

  printf("var: %s\n", var);
  printf("The size of «Hi» is %ld bytes.\n", sizeof("Hi"));

  return 0;
}