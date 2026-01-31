# Bitwise operators

Las operaciones bitwise (bit a bit) en RISC-V se realizan sobre registros. El ancho de la operación es igual al ancho del registro (XLEN). En nuestro emulador RV32, las operaciones son de 32 bits.

Si se requieren operaciones de 64 bits (por ejemplo con uint64_t), el compilador las implementa automáticamente usando varios registros y múltiples instrucciones de 32 bits para simular la operación.


## Left/Right Shift

- **Left Shift:** `<<`
- **Right Shift:** `>>`


### Left Shift  (sll / slli)

```
Original:
[0][0][1][0][1][1][0][1]

<< 1

Resultado:
[0][1][0][1][1][0][1][0]
```

Reglas:

- Todo se mueve ← izquierda
- Entra 0 por la derecha
- Se pierde el bit que sale por la izquierda
- Equivale a multiplicar

```
<< 1  = ×2
<< n  = ×2^n
```

### Right Shift lógico  (srl / srli)  - unsigned

```
Original:
[0][0][1][0][1][1][0][1]

>> 1

Resultado:
[0][0][0][1][0][1][1][0]
```

Reglas:

- Todo se mueve → derecha
- Entran 0s por la izquierda
- Para números SIN signo
- Aproxima división

```
>> 1 = ÷2
```

### Right Shift aritmético  (sra / srai)  - signed

```
Original (negativo, MSB=1):
[1][0][1][0][1][1][0][1]

>> 1

Resultado:
[1][1][0][1][0][1][1][0]
```

Reglas:

- Todo se mueve → derecha
- Se copia el bit de signo (MSB)
- Mantiene el signo del número

## Bitwise NOT  (~x)

Invierte TODOS los bits:
0 → 1
1 → 0

También se llama:

- complemento a uno
- inversión de bits

```
Original:
[0][0][1][0][1][1][0][1]

NOT (~)

Resultado:
[1][1][0][1][0][0][1][0]
```
<!--  -->
Visualmente:

```
Antes :  0 0 1 0 1 1 0 1
Después: 1 1 0 1 0 0 1 0
           ↑ ↑ ↑ ↑ ↑ ↑ ↑ ↑
           todo se invierte
```


Matematicamente:

```
~x = (2^n - 1) - x

donde n = número de bits

Ejemplo (8 bits):
~45 = 255 - 45 = 210
```

## Explorando el assembly

Montamos este snippet para explorar las operaciones bitwise a nivel assembly.

```c
void piyush() {
  int a = 0xA1;
  int b = 0x52;
  int c = 0x0;

  c = a & b;
  c = 0x0;

  c = a | b;
  c = 0x0;

  c = a ^ b;
  c = 0x0;

  c = ~a;
}
```

Esto se traduce en el siguiente codigo assembly:

```
	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	piyush
	.type	piyush, @function
piyush:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,161
	sw	a5,-20(s0)
	li	a5,82
	sw	a5,-24(s0)
	sw	zero,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	and	a5,a4,a5  #  c = a & b
	sw	a5,-28(s0)
	sw	zero,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	or	a5,a4,a5  #  c = a | b
	sw	a5,-28(s0)
	sw	zero,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	xor	a5,a4,a5  #  c = a ^ b
	sw	a5,-28(s0)
	sw	zero,-28(s0)
	lw	a5,-20(s0)
	not	a5,a5  #  c = ~a
	sw	a5,-28(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

Bicheamos un poco mas profundo con el siguiente pipeline, para ver como todo se produce a nivel de registros (en este caso entre a4 y a5):

1. make
2. make startqemu  // matamos la sesion con Ctrl+A X
3. make connect gdb

```gdb
>>> b piyush
>>> c # continue
>>> n # next avanza al siguiente statement de C, para ir instruccion a instruccion: ni o next instruction
>>> q
```

Vamos a explorar ahora que pasa con las operaciones shift entre bambalinas.

```c
void piyush() {
  int a = 0x1;
  int c;

  c = a << 1;
  c = a << 3;
  c = a << 31;
  c = a << 33; // OJO esto de aqui nos mete overflow en el registro
               // Lo que hace es curioso, OJO no es un regla, al hacer overflow al registro mueve el 1 de forma circular 33 posiciones y se convierte en un 2
               // NO esperar este resultado si tuy shift esta mas alla de los limites de los registros que andas manejando
               // 0000 0000 0000 0000 0000 0000 0000 0001 = 0x1
               // 0000 0000 0000 0000 0000 0000 0000 0010 = 0x2 (0x1 << 33)

  a = 0x80000000;
  c = a >> 31; // Como es entero con signo y el signo es 1 deberia computar todo 1's
               // 1000 0000 0000 0000 0000 0000 0000 0000 = 0x80000000
               // 1111 1111 1111 1111 1111 1111 1111 1111 = 0xFFFFFFFF

  unsigned int b = 0x80000000;
  c = b >> 31; // Al ser unsigned somo hace el shift logico, no aritmetico
               // 1000 0000 0000 0000 0000 0000 0000 0000 = 0x80000000
               // 0000 0000 0000 0000 0000 0000 0000 0001 = 0x00000001
}
```

```assembly
	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1_m2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.align	2
	.globl	piyush
	.type	piyush, @function
piyush:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	slli	a5,a5,1
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,3
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	slli	a5,a5,31
	sw	a5,-24(s0)
	li	a5,33
	lw	a4,-20(s0)
	sll	a5,a4,a5
	sw	a5,-24(s0)
	li	a5,-2147483648
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	srai	a5,a5,31
	sw	a5,-24(s0)
	li	a5,-2147483648
	sw	a5,-28(s0)
	lw	a5,-28(s0)
	srli	a5,a5,31
	sw	a5,-24(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```