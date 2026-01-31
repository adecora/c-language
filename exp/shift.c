#include <stdio.h>

int main() {

  long int a = 0x1;
  printf("a = 0x%lX\n", a);
  printf("a << 3  = 0x%lX\n ", a << 3); // a * 2^3
  printf("a << 63 = 0x%lX\n", a << 63);
  // El compilador chilla las operaciones se hacen en registro que con 64bits en total estamos tirando un oveflow del registro moviendo 64 posiciones
  // printf("a << 64 = 0x%lX\n", a << 64);

  a = 0x8;
  printf("\na = 0x%lX\n", a);
  printf("a >> 1 = 0x%lX\n", a >> 1); // a / 2^1
                                      // Ejemplos con 32bits en verdad esta maquina 64bits solo extenderiamos
                                      // 0000 0000 0000 1000 = 0x8
                                      // 0000 0000 0000 0100 = 0x4
  a = -0x8;
  printf("\na = 0x%lX\n", a);
  printf("a >> 1 = 0x%lX\n", a >> 1); // 1111 1111 1111 1000 = 0xFFF8
                                      // 1111 1111 1111 1100 = 0XFFFC

  return 0;
}