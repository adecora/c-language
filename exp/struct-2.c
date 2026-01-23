// cc -o main struct-2.c && ./main
#include <stdio.h>

struct complex_num {
  float a;
  float b;
};


int main() {
  struct complex_num num = {10 , 20}; // Inicializamo los valors en la definición

  printf("struct complex_num num = {a: %.2f, b:%.2f}\n", num.a, num.b);

  // Para acceder dentro una struct usamos la dotnotation
  num.a = 2.0;
  num.b = 5.0;

  printf("struct complex_num num = {a: %.2f, b:%.2f}\n", num.a, num.b);
  printf("sizeof(num): %ld bytes\n", sizeof(struct complex_num));
  printf("num = {'a': %ld bytes, 'b': %ld bytes}\n", sizeof(num.a), sizeof(num.b));
  printf("&num: %p\n", &num);
  printf("&num.a: %p\n", &num.a);
  printf("&num.b: %p\n", &num.b);

  return 0;
}