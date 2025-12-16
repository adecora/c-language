# const keyword

La keyword **const** significa que la variable que definimos es **read-only**, pero esto no nos impide que la podamos modificar.

```c
int piyush() {

  const float xyz = 5.0;

  return 0;
}
```

Si intentamos modificar la variable

```c
int piyush() {

  const float xyz = 5.0;

  xyz = 10.123;

  return 0;
}
```

El compilador nos chistará con un error:

```bash
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld n.s c-asm.c -o main.elf
c-asm.c: In function 'piyush':
c-asm.c:7:7: error: assignment of read-only variable 'xyz'
    7 |   xyz = 10.123;
      |       ^
make: *** [Makefile:11: piyush] Error 1
```

Podemos intentar ser trickies

```c
int piyush() {

  const float xyz = 5.0;

  *(&xyz) = 10.123;

  return 0;
}
```

Pero el compilador no cae en la trampa y reconoce que estamos intentando modificar un valor **read-only**.

```bash
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld n.s c-asm.c -o main.elf
c-asm.c: In function 'piyush':
c-asm.c:7:11: error: assignment of read-only variable 'xyz'
    7 |   *(&xyz) = 10.123;
      |           ^
make: *** [Makefile:11: piyush] Error 1
```

Sin embargo si intentamos lo mismo, pero creando un puntero aparte que apunte a nuestro **const** value.

```c
int piyush() {

  const float xyz = 5.0;

  float *p_xyz = &xyz;

  *p_xyz = 10.123;

  return 0;
}
```

En este caso el compilador nos chiva un warning pero nos deja modificar el valor.

```bash
riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld n.s c-asm.c -o main.elf
c-asm.c: In function 'piyush':
c-asm.c:5:18: warning: initialization discards 'const' qualifier from pointer target type [-Wdiscarded-qualifiers]
    5 |   float *p_xyz = &xyz;
      |                  ^
riscv64-unknown-elf-objcopy -O binary main.elf main.bin
```