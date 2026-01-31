void piyush() {
  int a = 0x1;
  int c;

  c = a << 1;
  c = a << 3;
  c = a << 31;
  c = a << 33;

  a = 0x80000000;
  c = a >> 31; // Como es entero con signo y el signo es 1 deberia computar todo 1's
               // 1000 0000 0000 0000 0000 0000 0000 0000 = 0x80000000
               // 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF

  unsigned int b = 0x80000000;
  c = b >> 31; // Al ser unsigned somo hace el shift logico, no aritmetico
               // 1000 0000 0000 0000 0000 0000 0000 0000 = 0x80000000
               // 0000 0000 0000 0000 0000 0000 0000 0001 = 0x00000001
}
