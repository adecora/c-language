#include <stdio.h>

// Arithmetic operators:
//  +: Addition
//  -: Subtraction
//  *: Multiplication
//  /: Division
//  %: Modulus (remainder after division)
// ++: Increment (increases value by 1)
// --: Decrement (decreases value by 1)

void main() {
  // int variable1, variable2, answer; // Si tenemos varias definiciones del mismo tipo podemos hacerlo de esta forma
  int variable1;  // definida pero no inicializada, el valor que tendrá es un garbage value, puede ser cualquier valor
  int variable2;
  int answer;

  // int variable1 = 10, variable2, answer; // Al definir varias funciones en una misma línea tmbn está permitido inicializar las variable
  variable1 = 2; // asignación, asigna el valor 10 a la variable variable1
  variable2 = 3;  // ¿Qué pasa si no asginamos un valor a variable2?

  float f1 = 2;
  float f2 = 3, fans;

  answer = variable1 + variable2;
  printf("+: %d\n", answer);

  answer = variable1 - variable2;
  printf("-: %d\n", answer);

  answer = variable1 * variable2;
  printf("*: %d\n", answer);

  answer = variable1 / variable2; // La división es 0 no 0.3333, se trata de un división de enteros
  printf("/: %d\n", answer);

  answer = variable1 % variable2;
  printf("%%: %d\n", answer);

  printf("\n");

  fans = f1 + f2;
  printf("+: %.2f\n", fans);

  fans = f1 - f2;
  printf("-: %.2f\n", fans);

  fans = f1 * f2;
  printf("*: %.2f\n", fans);

  fans = f1 / f2; // Con que sólo uno de los operandos sea float la respuesta es float, y si la variable a la que estamos asignando el resultado es integer el resultado se castea
  printf("  fans = f1/f2: %.2f\n", fans);

  fans = variable1 / f2;
  printf("  fans = v1/f1: %.2f\n", fans);

  answer = f1 / f2; // La opración devuelve un float pero al asignarlo a un entero se castea a entero, 0
  printf("answer = f1/f2: %d\n", answer);

  fans = (int)f1 % (int)f2; // La operación módulo sólo disponible para enteros, tengo que castear
  printf("%%: %.2f\n", fans);

  printf("\n");

  int i = 10;

  printf("  i: %d\n", i);
  printf("i++: %d\n", i++); // Primero usa el valor actual de i y luego incrementa
  printf("  i: %d\n", i);
  printf("++i: %d\n", ++i); // Pimero incrementa y usa el valor actualizado de i
  printf("  i: %d\n", i);
}