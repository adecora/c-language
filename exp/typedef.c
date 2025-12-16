#include <stdio.h>

typedef unsigned char piyush;  // Crea un alias `piyush` para las variables tipo `unsigned char`

void main() {
  piyush a = 10;

  printf("%ld\n", sizeof(a));      // Obtenemos el `sizeof` tamaño en bytes de una variable
  printf("%ld\n", sizeof(piyush)); // Podemos obtener tmbn el `sizeof` de un tipo de dato
}