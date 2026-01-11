#include <stdio.h>


// int a = 10;
// int b = 20;
// int *ptr;

// ptr = &a;

// // Puedo reasignar el puntero las veces que me salga del toto
// ptr = &b;

// char number[4];
// char *c_ptr;

// c_ptr = &number;    // Apunta a la dircción de memoria en la que empieza el array
// c_ptr = &number[0]; // Equivalente de la mierda anterior

// number = xyz; // NOOOOO!!!! la principal diferencia no está permitido reasignar un array una vez declarado


int main() {

  char number[] = "Hi!";
  char *str;

  char *msg1 = "Hi!";
  char *msg2 = "Hello, World!";

  str = msg1;
  printf("str -> msg1: %s\n", str);

  str = msg2;
  printf("str -> msg2: %s\n", str);

  printf("number[]: %s\n", number);

  // number = msg1; // Nanay colega, ya dijimos que no se puede esta vaina: “error: assignment to expression with array type”

  return 0;
}