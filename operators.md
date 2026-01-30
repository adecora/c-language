# Types of Operators

- **Arithmetics:** +, -, *, /, %
- **Relational:** <, >, ==, !=, <=, >=
- **Logical:** OR, AND, NOT
- **Bitwise operators**

**also:**

- **Assigment:** =, +=, -=
- **Conditional:** condition?true:false
- **On pointers**


## Arithmetics

Un chekeo a que vainas nos sacan los operadores aritmeticos en asembly.

```c
void piyush() {
  int a = 2;
  int b = 3;
  int c;

  c = a + b;

  c = a - b;

  c = a * b;

  c = a / b;

  c = a++;

  c = ++a;
}
```


```assembly
	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.globl	__mulsi3
	.globl	__divsi3
	.align	2
	.globl	piyush
	.type	piyush, @function
piyush:

# Remember e stack crece hacia abajo
# Direcciones altas
# ┌──────────────┐  ← sp (antes)
# │              │
# └──────────────┘
# Direcciones bajas

# Hace espacio para el stack y salva el valor de un par de registros
	addi	sp,sp,-32
	sw	ra,28(sp)
	sw	s0,24(sp)
	addi	s0,sp,32

# Direcciones altas
# ┌──────────────┐
# │              │
# ├──────────────┤ ← s0 (nuevo frame pointer)
# │  ra   (28)   │
# ├──────────────┤
# │  s0   (24)   │
# ├──────────────┤
# │              │
# │ variables    │
# │ locales      │
# │              │
# ├──────────────┤ ← sp (nuevo)
# Direcciones bajas

	li	a5,2       # <- a
	sw	a5,-20(s0)
	li	a5,3       # <- b
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)

# c = a + b
	add	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)

# c = a - b
	sub	a5,a4,a5
	sw	a5,-28(s0)

# Ojo el compilador sin el set de instrucciona mul
# hace la ñapa, llama a `__mulsi3`

  # Le pasamos los parámetros a0 y a1
  lw	a1,-24(s0)
	lw	a0,-20(s0)

  call	__mulsi3
  # El resultado vuelve en a0
	mv	a5,a0
	sw	a5,-28(s0)
	lw	a1,-24(s0)
	lw	a0,-20(s0)
	call	__divsi3
	mv	a5,a0
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	addi	a4,a5,1
	sw	a4,-20(s0)
	sw	a5,-28(s0)
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-20(s0)
	sw	a5,-28(s0)
	nop
	lw	ra,28(sp)
	lw	s0,24(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

Añadimos la extensión **M (Multiply/Divide)** a nuestro `make assembly` y tenemos: `riscv64-unknown-elf-gcc -O0 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld c-asm.c -S`.

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
	li	a5,2
	sw	a5,-20(s0)
	li	a5,3
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	add	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sub	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)

# Ahora si tenemos el set de intrucciones con multiplicar
	mul	a5,a4,a5
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)

# c = a / b
	div	a5,a4,a5
	sw	a5,-28(s0)

# c = a++
	lw	a5,-20(s0)
	addi	a4,a5,1   # En el registro 4 guarda el valor de a + 1
	sw	a4,-20(s0)  # Guarda como valor de el registro 4
	sw	a5,-28(s0)  # Guarda como valor de c el registro 5, a antes de la suma

# c = ++a
	lw	a5,-20(s0)  # Cargar a en el registro 5
  addi	a5,a5,1   # Sumar 1
	sw	a5,-20(s0)  # Guardar el valor como a
	lw	a5,-20(s0)  # Carga el valor
	sw	a5,-28(s0)  # Guardar el valor como c
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

## Relational operators

Usamos el siguiente snippet para bichear el assembly:

```c
void piyush() {
  int a = 127;
  int b = 5;
  int c;

  c = a > b;
  c = a >= b;

  c = a < b;
  c = a <= b;

  c = a == b;
  c = a != b;
}
```

Que nos devuelve:

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
	li	a5,127
	sw	a5,-20(s0) # Guarda a en -20
	li	a5,5
	sw	a5,-24(s0) # Guarda b en -24
	lw	a4,-20(s0)
	lw	a5,-24(s0)
# c = a > b;
	sgt	a5,a4,a5     # greater than devuelve 1 o 0
	andi	a5,a5,0xff # Asegura que el resultado de sgt sea 8 bits
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)

# c = a >= b
	slt	a5,a4,a5  # Estas dos operacione implementan mayor o igual como no menor
	seqz	a5,a5   # !(<)
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	slt	a5,a4,a5
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sgt	a5,a4,a5
	seqz	a5,a5
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
# c = a == b
	sub	a5,a4,a5 # Otra triquiñuela sin son iguales la resto 0
	seqz	a5,a5  # Si zero seteo a 1 si no seteo a 0
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	lw	a4,-20(s0)
	lw	a5,-24(s0)
	sub	a5,a4,a5
	snez	a5,a5
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

## Operadores lógicos

Partimos de:

```c
void piyush() {
  int a = 3;
  int b = 5;
  int c;

  c = a && b;
  c = a || b;
  c = !a;
}
```

Generamos el assembly de esta vaina:

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
	li	a5,3
	sw	a5,-20(s0)  # Valor de a en -20
	li	a5,5
	sw	a5,-24(s0)  # Valor de b en -24

# c = a && b
  lw	a5,-20(s0)
  # Primero chekeo a si es 0 ya salor a .L2 y seteo el resultado como 0
	beq	a5,zero,.L2
	lw	a5,-24(s0)
  # Si a no es 0 checkeo b si e 0 salto a .L2, sin sigue p'alante y setea el resultado a 1
	beq	a5,zero,.L2
	li	a5,1
	j	.L3
.L2:
	li	a5,0
.L3:

# c = a || b
	sw	a5,-28(s0)
	lw	a5,-20(s0)
  # Misma vaina pero ahora si a no es cero seteo el resultado a 1 llendome a .L4
	bne	a5,zero,.L4
	lw	a5,-24(s0)
  # Ahora compruebo b si es zero salto a .L5 a setear a zero el resultado si no sigo a .L4 a ponerlo a 1
	beq	a5,zero,.L5
.L4:
	li	a5,1
	j	.L6
.L5:
	li	a5,0
.L6:
	sw	a5,-28(s0)

# c = !a
	lw	a5,-20(s0)
	seqz	a5,a5
	andi	a5,a5,0xff
	sw	a5,-28(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```