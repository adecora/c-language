#include <stdio.h>


struct pixel_t { // _t es una convención para decir pixel **data type**
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

struct test1_t { // El total del nuestra struct test_t debería ser 7 bytes
  unsigned char r; // 1 byte
  unsigned char g; // 1 byte
  unsigned char b; // 1 byte

  int l;           // 4 bytes
};

// __attribute__ es una keyword para el compilador gcc, no para C que le indica oye, no añadas el byte de padding a esta struct
struct test2_t {
  int l;           // 4 bytes

  unsigned char r; // 1 byte
  unsigned char g; // 1 byte
  unsigned char b; // 1 byte
} __attribute__((packed));

void main() {
  struct pixel_t p;

  printf("%ld\b\n", sizeof(p));
  printf("%ld\b\n", sizeof(struct test1_t)); // Pinta 8 bytes
  // gcc añade un byte de padding después de rbg
  // <- 1 byte -> <- 1 byte -> <- 1 byte -> <- 1 byte -> <- 4 byte ->
  // |     r     ||     g     ||     b     ||  padding  ||     l     |

  printf("%ld\b\n", sizeof(struct test2_t)); // Pinta 8 bytes
}