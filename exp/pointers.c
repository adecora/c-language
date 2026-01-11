#include <stdio.h>

// Página para trastear con punteros: https://eseo-tech.github.io/emulsiV/

//                  ←────── 4 bytes ──────→
//             +------+------+------+------+
// 0x00  ───→  |  00  |  01  |  02  |  03  |
//             +------+------+------+------+
// 0x04  ───→  |  04  | //// |      |      |
//             +------+------+------+------+
// 0x08  ───→  |      |      |      |      |
//             +------+------+------+------+
//             |      |      |      |      |
//             +------+------+------+------+

//    pointer (valor = 0x08) => Apunta a la dirección de memoria 0x08
//            |
//            v
//      +------------------------------+
//      |  0x08  |  dirección guardada |
//      |        |  tamaño del pointer |
//      +------------------------------+
//                 arch 32 / 64 bits => El tamaño del puntero depende de la arquitectura de la máquina
//                                      32/64 bits, lo necesario para poder representar todas la direcciones de memoria
//                                      - 2^32 = 4294967296 = 4Gb
//                                      - 2^64 = 18446744073709551616 = 16EB hexabits -> no todos lo bits se usan -> x86-64 usa 48 bits efectivos


// Tenemos tres tipos de punteros:
//   - Void pointers: simplemente contiene una dirección de memoria | La diferencia queda clara cuando vemos la aritmetica de los punteros
//   - Data pointers:                                               |
//       • Cuando tenemos un puntero apuntando una dirección de memoria, el data type convence al compilardor:
//          «Oie este puntero es integer, cuando leas el valor lee cuatro siguientes bytes desde la dirección de memoria»
//   - Function pointers


int main() {

  char abc = 'Z';

  char *ptr; // char* ptr; char * ptr;  tmbn son válidas

  // ptr = 0x1234; => Guarda esta dirección en el puntero ptr
  // *ptr = 'A';   => Guarda el caracter 'A' en la dirección que está guardada en ptr (0x1234)

  char number[4] = {0};
  number[0] = 'A'; // 65 en decimal, como es little endian vamos a leer 65 el resto de caracter de number inicalizados a 0

  //  Hardcodear direcciones de memoria en código real... Dangerous, probablemente salte segmentation fault
  int *in_ptr = (int *)0x1234; // El cast fuerza a convertirse a una puntero a un entero
                               // En sistemas de de 64bits un `int` normalmente 32bits pero un puntero 64bits, si la dirección mayor puede haber pérdida o truncamiento de datos
                               // (int *)(uintptr_t)0x1234; => `uintptr_t`, tipo entero diseñado para almacenar direcciones de memoria, mismo tamaño que el puntero
  printf("in_ptr: %p\n", in_ptr);
  // printf("*in_ptr: %d\n", *in_ptr); // segmentation fault, lo dicho esta direccion de memoria no está permitida meu!!!

  in_ptr = (int *)&number[0]; // (int *) &number; tmbn es valida esta vaina
  printf("in_ptr: %p\n", in_ptr);
  printf("*in_ptr: %d\n", *in_ptr);

                        //  Cuando en memoria la mierdas se representan en el mismo orden que nosotros lo escribimos
                        //  El byte más significativo (el "extremo grande") primero, en la dirección de memoria más baja
                        //  Empieza por el Big
                        //
                        //      offset:      0          1          2          3
                        //               ← 1byte →  ← 1byte →  ← 1byte →  ← 1byte →
                        //  Big Endian: |    00   ||    21   ||    49   ||    48   |


  *in_ptr = 0x00214948; // <= Esta vaina Little Endian:
                        // El byte menos siginificativo 0x48 se está guardando en la dirección de memoria más baja: “number[0]”

                        //  Cuando en memoria la mierdas se representan en el mismo orden inverso con el que lo escribimos
                        //  El byte menos significativo (el "extremo pequeño") primero, en la dirección de memoria más baja
                        //  Empieza por el Little
                        //
                        //        offset:      0          1          2          3
                        //                 ← 1byte →  ← 1byte →  ← 1byte →  ← 1byte →
                        // Little Endian: |    48   ||    49   ||    21   ||    00   |
  int i = 0;
  while (i < 4) {
    printf("number[%d] = %c\n", i, number[i]);
    ++i;
  }
  printf("number[]: %s\n", number);


  printf("Pointer address: %p\n", ptr);
  printf("Pointer value  : %c\n", *ptr); // No está inicializado apunta a una dirección random de memoria, que tiene dentro¿?¿? Pura garbage mierdecilla

  ptr = &abc; // => Guarda en prt la dirección de la variable abc

  printf("Pointer address: %p\n", ptr);
  printf("Pointer value  : %c\n", *ptr);

  printf("&abc: %p, ptr: %p, sizeof(ptr): %ld\n", &abc, ptr, sizeof(ptr));

  printf("Pointer (actual) address: %p\n", ptr);
  printf("Pointer (next) address  : %p\n", (ptr + 1));

  *ptr = 'A'; // Modifica el carcater guardado en la dirección en la que está apuntando ptr

  printf("abc: %c, *ptr: %c\n", abc, *ptr);

  return 0;
}