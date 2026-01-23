// cc -o main union-2.c && ./main
#include <stdio.h>

union abc {
  int a;
  short b;
  char c;
};

int main () {
  // Ver: https://www.scadacore.com/tools/programming-calculators/online-hex-converter/
  // lscpu | grep -i endian
  // Byte Order:                           Little Endian

  // union abc u = { 17433921 }; // 01 0A 05 41
  union abc u = { 0x010A0541 }; // 17433921
  // u.a (int)   == 01 0A 05 41 == 17433921
  // u.a (short) ==       05 41 ==     1345
  // u.a (char)  ==          41 ==       65

  printf("sizeof(union): %ld\n", sizeof(union abc));
  printf("sizeof(int): %ld\n", sizeof(int));
  printf("sizeof(short): %ld\n", sizeof(short));
  printf("sizeof(char): %ld\n", sizeof(char));

  printf("&u: %p\n", &u);
  printf("&u: %p\n", &u.a);
  printf("&u: %p\n", &u.b);
  printf("&u: %p\n", &u.c);

  printf("u.a: %d\n", u.a);
  printf("u.b: %d\n", u.b);
  printf("u.c: %d\n", u.c);

  printf("u.a (%%X): %#08X\n", u.a);
  printf("u.b (%%X): %#08X\n", u.b);
  printf("u.c (%%X): %#08X\n", u.c);

  return 0;
}