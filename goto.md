# goto

Sirve para movermos hasta una etiqueta que hayamos definido dentro de una misma función.

```c
void piyush() {
  int i = 10;

  goto end;

  i = i + 2;

  end:
    i = i + 21;

  return;
}
```
El assembly se fuma el salto ya que el código generado por el compilador se da cuenta que es imposible llegar a ese bloque de código y ejecuta directamente la instrucción del `goto`.

```assembly
	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1"
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
	li	a5,10
	sw	a5,-20(s0)
	nop
.L2:
	lw	a5,-20(s0)
	# El compilador optimiza el código se fuma el salto y el `i = i + 2` que nunca se va a ejecutar y hace directamente `i = i + 21`
	addi	a5,a5,21
	sw	a5,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

Vamos a mierdear un poco el código para que el compilador si genere el salto de `goto`.

```c
void piyush() {
  int i = 10;

  if (i == 12) {
    goto end;
  }

  i = i + 2;

  end:
    i = i + 21;

  return;
}
```

```assembly
	.file	"c-asm.c"
	.option nopic
	.attribute arch, "rv32i2p1"
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
	li	a5,10
	sw	a5,-20(s0)
	lw	a4,-20(s0)
	li	a5,12
	# Condición para entrar en el `if` a4 (i) == a5 (12), en ese caso salta a .L5 lanza el `goto` al tiro
	beq	a4,a5,.L5
	# Si la condición del `if` no se cumple `i = i + 2`
	lw	a5,-20(s0)
	addi	a5,a5,2
	sw	a5,-20(s0)
	j	.L3
.L5:
	nop
.L3:
	# `goto` statement `i = i + 21`
	lw	a5,-20(s0)
	addi	a5,a5,21
	sw	a5,-20(s0)
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

---

El ciclo de vida de un etiqueta como `end` es dentro del mismo scope, al lanzar `goto end;` dentro de `piyush` la etiqueta `end` tiene que estar definida dentro del scope de la función `piyush` si no, no tiene ni zorra de a donde tiene que saltar, *el propio compilador se queja y no nos deja compilar*.

```c
void piyush2() {
  end:
    i = i + 21;
}

void piyush() {
  int i = 12;

  if (i == 12) {
    goto end;
  }

  return;
}
```