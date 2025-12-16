#include <stdio.h>


union union_t {
  char a;
  short b;
};
// gcc va alojar dos bytes para b y el primero de los bytes de b va a ser el byte para a
// <- 1 byte -> <- 1 byte ->
// |     a     |
// |           b            |
// Mientras que struct aloja memoria en serie para cada uno de sus miembros
// union aloja la máxima capacidad que requiere el mayor de sus miembros y el resto de miembros rehusan el mismo espacio

void main() {
  union union_t p;


  printf("%ld\b\n", sizeof(union union_t));
}