#include <stdio.h>

int main () {
  int a[5] = {1, 2, 3, 4, 5}; // Inicializamos el array

  printf("size of a[]: %ld bytes\n", sizeof(a));  // 20 bytes = 4 bytes por int * 5 enteros


  // «a» apunta al inicio del array
  //             a[0]         a[1]         a[2]         a[3]         a[4]     lenght = 5
  //   a -> <- 4 byte -> <- 4 byte -> <- 4 byte -> <- 4 byte -> <- 4 byte ->
  //          |     1     |     2      |     3      |      4     |     4     |

  for (int i=0; i < 5; i++) {
    printf("a[%d] = %d ó *(a + %d) = %d\n", i, a[i], i, *(a + i)); // Tmbn se puede acceder como el valor al que apunta *(a + i), a tiene
  }                                                                // que hacer referencia al una dirección de memoria el + 1, 2, 3...
                                                                   // infiere el tipo tipo del puntero y automáticamente avanza a la siguiente dirección
                                                                   // si es char* 0xF0 -> 0xF1
                                                                   // si es int*  0xF0 -> 0xF4

  for (int i=5; i < 10; i++) {
    printf("a[%d] = %d\n", i, a[i]); // Pinta mierdas está accedienco a posiciones de memoria que no debería acceder tiene otras vainas chunk info o whatever
  }                                  // si resulta que se puede traducir al tipo del puntero int pues vemos numeros random si no welcome to «segmentation fault»


  unsigned int b[3] = { 1107312896, 1140867840 };
  // En hexadecimal tenemos que estos enteros son:
  //     1107312896 = 0x42004100
  //     1140867840 = 0x44004300


  // Como esta vaina es Little Endian el byte menos significativo va primero
  //
  // b[0] = 0x42004100
  //   Dirección →   +0    +1    +2    +3
  //   Bytes      | 00 | 41 | 00 | 42 |
  //   ASCII      | \0 |  A | \0 |  B |

  // b[1] = 0x44004300
  //   Dirección →   +4    +5    +6    +7
  //   Bytes      | 00 | 43 | 00 | 44 |
  //   ASCII      | \0 |  C | \0 |  D |

  // char *p = (char *) b; <== Esta vaina apunta ahora a la misma memoria pero byte a byte porque el puntero es de tipo char
                            // IMPORTANTE!!! Esta mierda importa al final cuando incrementamos un array a[0]..a[1] ó *(a + 0)...*(a + 1)
                            // el número de elmentos que avanza en memoria viene condicianado por data type con el que se definimos el array

  //
  //   Dirección relativa →
  //    +0  +1   +2  +3  +4  +5  +6  +7
  //   ┌───┬───┬───┬───┬───┬───┬───┬───┐
  //   │00 │41 │00 │42 │00 │43 │00 │44 │
  //   │\0 │ A │\0 │ B │\0 │ C │\0 │ D │
  //   └───┴───┴───┴───┴───┴───┴───┴───┘
  //    ↑                              ↑
  //    b[0]                           b[7]



  for (int i = 0; i < 2; i++) {
    printf("b[%d] = %d\n", i, b[i]);
  }

  char *p = (char *) b;

  for (int i = 0; i < 8; i++) {
    printf("p[%d] = %c\n", i, p[i]);
  }


  return 0;
}