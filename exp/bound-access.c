// Compilamos con `gcc -ggdb bound-access.c`
// | Flag   | Descripción |
// |--------|------------|
// | `-g`   | Información de debug genérica (DWARF estándar) |
// | `-ggdb`| Debug **específico para GDB**, con extensiones |
// | `-g0`  | Sin información de depuración |
// | `-g1`  | Información mínima |
// | `-g2`  | Nivel por defecto (equivalente a `-g`) |
// | `-g3`  | Incluye macros en la información de depuración |

// Debuggeamos con `gdb a.out`
// > break main # Punto de ruptura en el main
// > r  # ó run Para arrancar el programa
// > n # ó next Avanza el siguiente statement (instrucción de C). OJO ni ó next instrucción avanza por la instrucciones de emsamblador
// > p a_shot # ó print a_short Imprime el valor por pantalla

// Vemos como cada posición de memoria del array está separada por 2bytes
//    >>> p &a_short[2]
//    $1 = (short *) 0x7fffffffcdaa
//    >>> p &a_short[0]
//    $2 = (short *) 0x7fffffffcda6
//    >>> p &a_short[1]
//    $3 = (short *) 0x7fffffffcda8

// Vemos como cada posición de memoria del array está separada por 4bytes
//    >>> p &a_int[1]
//    $4 = (int *) 0x7fffffffcdb4
//    >>> p &a_int[0]
//    $5 = (int *) 0x7fffffffcdb0
//    >>> p &a_int[2]
//    $6 = (int *) 0x7fffffffcdb8
//

// Cuando definimos un array al inferir el datatype C sabe como tiene que avanzar para acceder a los elementos del array, es una operación matemática:
// a_int + 5 * sizeof(int) = desplazamiento de 20 bytes

// PERO no tiene ni zorra del tamaño de array
// a_int + 5    → &a_int[5] <- X fuera del array sin embargo es una operación permitida
//                             No está capado que accedamos a esa posición de memoria y podemos sobreescribirla ahora estamos pisando
//                             memoria regalada no es nuestra podemos liar un buffer overflow

// ↑ direcciones más altas
// │
// │   ┌───────────────┐
// │   │   basura /    │  ← memoria fuera del array
// │   │   overflow    │
// │   ├───────────────┤
// │   │      51       │  a_int[4]
// │   ├───────────────┤
// │   │      41       │  a_int[3]
// │   ├───────────────┤
// │   │      31       │  a_int[2]
// │   ├───────────────┤
// │   │      21       │  a_int[1]
// │   ├───────────────┤
// │   │      11       │  a_int[0]
// │   └───────────────┘  ← a_int (base del array)
// │
// ↓ direcciones más bajas


#include <stdio.h>

int main() {

  // Debido al datatype definido cuando creamos el array
  short int a_short[5] = {10, 20, 30, 40, 50};  // a_short[2] sabe que tiene que avanzar 4bytes (2bytes * 2elementos) para obtener el índice 2
  int a_int[5] = {11, 21, 31, 41, 51};          // a_int[2] sabe que tiene que avanzar 8bytes (4bytes * 2elemntos) para obtener el índice 2

  a_int[3] = 45;
  printf("a_int[3]: %d\n", a_int[3]);

  int x = 99;
  x = a_int[4];
  printf("x: %d\n", x);

  // Pinta el tamaño del array entero
  printf("sizeof(a_short): %ld\n", sizeof(a_short)); // 10bytes = 2bytes elemento * 5 elementos
  printf("sizeof(a_int): %ld\n", sizeof(a_int)); // 20bytes = 4bytes elemento * 5 elmentos

  return 0;
}