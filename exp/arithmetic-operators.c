#include <stdio.h>

int main() {
  int a = 9;
  int b = 4;
  // No sólo int esta vaina tmbn rula en chars
  // char a = 9;
  // char b = 4;

  printf("a + b = %d\n", a + b);
  printf("a - b = %d\n", a - b);
  printf("a * b = %d\n", a * b);
  printf("a / b = %d\n", a / b);
  printf("a %% b = %d\n", a % b);

  printf("\na = %d\n", a);
  printf("a++ = %d\n", a++);
  printf("a = %d\n", a);
  printf("++a = %d\n", ++a);
  printf("a = %d\n", a);

  // Ojo que si hacemos operaciones aritmeticas en chars, remeber sólo 8bytes
  // como es signed el 8bit es de signo
  char c = 127;

  printf("\nc = %d\n", c);
  printf("++c = %d\n", ++c);
  printf("c = %d\n", c);
  printf("++c = %d\n", ++c);


  return 0;
}