#include <stdio.h>

int main() {

  int a = 0x01;
  int b = 0x02;

  printf("a = 0x%X\n", a);
  printf("b = 0x%X\n", b);

  printf("\na & b = 0x%X\n", a & b);
  printf("a | b = 0x%X\n", a | b);


  a = 0xA1; //         1010 0001
  b = 0x52; //         0101 0010
            // a & b = 0000 0000
            // a | b = 1111 0011 -> 0xF3
            // a ^ b = 1111 0011 -> 0xF3
            //    ~a = 0101 1110 -> 0x5E } OJO los 3bytes restantes de a y b para completar la size de registro 32bits (4bytes)
            //    ~b = 1010 1101 -> 0xAD } tmbn se invierten

  printf("\na = 0x%X\n", a);
  printf("b = 0x%X\n", b);

  printf("\na & b = 0x%X\n", a & b);
  printf("a | b = 0x%X\n", a | b);
  printf("a ^ b = 0x%X\n", a ^ b);
  printf("   ~a = 0x%X\n", ~a);
  printf("   ~b = 0x%X\n", ~b);

  // file a.out
  // a.out: ELF 64-bit
  // En este caso 64bit, las operaciones bitwise se realizan en los registros de 64bits siempre pero si usamos operadores mas pequeños se descarta el resto del tamaño
  long int x = 0xA1;
  long int y = 0x52;

  printf("\nx = 0x%lX\n", x);
  printf("y = 0x%lX\n", y);

  printf("\nx & y = 0x%lX\n", x & y);
  printf("x | y = 0x%lX\n", x | y);
  printf("x ^ y = 0x%lX\n", x ^ y);
  printf("   ~x = 0x%lX\n", ~x);
  printf("   ~y = 0x%lX\n", ~y);

  return 0;
}