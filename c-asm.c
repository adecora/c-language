int piyush() {

  volatile int i = 10;

  i = i + 1;
  i = i + 10;

  return i;
}