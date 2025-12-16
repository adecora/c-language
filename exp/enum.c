#include <stdio.h>

// enum es una colección de integers de forma incremental comenzando en 0 si no provee una valor incial
// podría incluso asignar un valor incial a cada uno de ellos
enum weekday_t {  // Los números se incrementan desde el valor inicial
  sunday = -2,
  monday,
  tuesday,
  wed = 7, // modifico la asignación original de wed y a partir de aquí se generan incrementales del nuevo valor de wed
  thursday,
  friday,
  saturday
};

void main() {
  enum weekday_t random_day;

  random_day = friday;

  printf("%d\n", tuesday);
  printf("%d\n", saturday);
}