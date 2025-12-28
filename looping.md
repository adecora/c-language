# do while

Vamos a empezar con el bucle `do-while`.

```c
void piyush() {
  int i  = 1;
  int j = 2;

  do {
    // Siempre se ejecuta una vez
    j = j + 1;
  } while (i == 2); // En caso que i==2 vuelve a repetir.

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
	li	a5,1
	sw	a5,-24(s0)
	li	a5,2
	sw	a5,-20(s0)
  # Inicio del `do-while` siempre se ejecuta como mínimo una vez
.L2:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a4,-24(s0)
	li	a5,2
  # Comprueba que a4 (i) es igual a a5 (2) si lo es vuele al inicio del `do-while` sin no continua con el código
	beq	a4,a5,.L2
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

---

```c
void piyush() {
  int i  = 1;
  int j = 2;

  do {
    // Se convierte en un bucle infinito
    j = j + 1;
  } while (i == 1); // Ahora siempre siempre se cumple la condición

  return;
}

---

```c
void piyush() {
  int i  = 10;
  int j = 2;

  do {
    // Se ejecutará hasta que se cumpla la condición i > 0
    j = j + 1;
    i = i - 1; // Lo más importante añadir la condición que nos permita salir del bucle
  } while (i > 0);
  // Al final el bucle se habrá ejecutado 10 veces i valdrá 0 y j 12

  return;
}



# while

Traducimos el `do-while` en un `while` loop.

```c
void piyush() {
  int i  = 1;
  int j = 2;

  while (i == 2) {
    j = j + 1;
  }

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
	li	a5,1
	sw	a5,-24(s0)
	li	a5,2
	sw	a5,-20(s0)
  # Salta a .L2 que contiene el código que evalua la condición para entrar en el while loop
	j	.L2
.L3:
  # Aquí está el código del `while`
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
.L2:
	lw	a4,-24(s0)
	li	a5,2
  # En caso que se cumpla la condición a4 (i) == a5 (2) entra en el loop, si no continua al final de código
	beq	a4,a5,.L3
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

---

```c
void piyush() {
  int i  = 1;
  int j = 2;

  while (i == 1) { // La condición siempre se cumple
    // Se convierte en un bucle infinito
    j = j + 1;
  }

  return;
}
```

---

```c
void piyush() {
  int i  = 10;
  int j = 2;

  while (i > 0) { // Estamos en el bucle hasta que i deje de ser mayor que 0
    j = j + 1;
    i = i - 1; // Importante añadir la condición para salir del bucle
  }
  // Al final el bucle se habrá ejecutado 10 veces i valdrá 0 y j 12

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
	li	a5,2
	sw	a5,-24(s0)
	j	.L2
.L3:
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
	lw	a5,-20(s0)
	addi	a5,a5,-1
	sw	a5,-20(s0)
.L2:
	lw	a5,-20(s0)
	bgt	a5,zero,.L3
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

# for

El `for-loop` es muy similar al `while` anterior con la única diferencia que combina todas las condiciones del `loop` en una única línea.

> `for(inicializa la variable; condición para salir del bucle; último statement del bucle instrucción para que la variable modifique su valor hasta que llegue a la condición de salida)`



```c
void piyush() {
  int j = 2;

  for (int i = 10; i > 0; i = i -1) {
    j = j + 1;
  }

  return;
}
```

El assembly es prácticamente igual al del `while-loop` con la diferencia que ahora se guarda primero la variable `j` en `-20(s0)` y luego `i` en `-24(s0)`

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
	# Primero se guarda j
	li	a5,2
	sw	a5,-20(s0)
  # Luego se guarda i
	li	a5,10
	sw	a5,-24(s0)
	j	.L2
.L3:
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-24(s0)
	addi	a5,a5,-1
	sw	a5,-24(s0)
.L2:
	lw	a5,-24(s0)
	bgt	a5,zero,.L3
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

**continue**

```c
void piyush() {
  int j = 2;

  for (int i = 10; i > 0; i = i -1) {
    j = j + 200;  // Sin esta instrucción el compilador se fuma el bucle
    continue;  // Cuando llega aquí vuelve al inicio del bucle
    j = j - 3;  // Nunca se llega a ejecutar
  }

  return;
}
```

Casos de uso, nos vale para saltarnos un turno del loop en el que no queremos ejecutar ninguna instrucción, *p.ej. decrementar j a no ser que i sea igual a 5*.

```c
void piyush() {
  int j = 2;

  for (int i = 10; i > 0; i = i -1) {
    if (i == 5) {
      continue;
    }
    j = j + 1;
  }

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
	li	a5,2
	sw	a5,-20(s0)
	li	a5,10
	sw	a5,-24(s0)
	j	.L2
.L5:
  # Contiene el cuerpo del loop
	lw	a4,-24(s0)
	li	a5,5
  # Si a4 (i) es igual a5 (5) salta a .L7 y fumate el decremento j
	beq	a4,a5,.L7
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	j	.L4
.L7:
  # Al saltar aquí se esta fumando la parte de decrementar j, el cuerpo del loop
	nop # simplemente consume un ciclo del reloj
.L4:
  # final del loop
	lw	a5,-24(s0)
	addi	a5,a5,-1
	sw	a5,-24(s0)
.L2:
  # Check de si tenemos que entrar al loop o seguir la vida
	lw	a5,-24(s0)
	bgt	a5,zero,.L5
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

Si modificamos el `continue` por un `break` en cuanto llegue a `5` se escapa del loop.

```c
void piyush() {
  int j = 2;

  for (int i = 10; i > 0; i = i -1) {
    if (i == 5) {
      break;
    }
    j = j + 1;
  }

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
	li	a5,2
	sw	a5,-20(s0)
	li	a5,10
	sw	a5,-24(s0)
	j	.L2
.L5
  # Inicio del loop
	lw	a4,-24(s0)
	li	a5,5
  # Si a4 (i) es igual a a5 (5) salta a .L7 que se va fuera del loop al final de la función
	beq	a4,a5,.L7
	lw	a5,-20(s0)
	addi	a5,a5,1
	sw	a5,-20(s0)
	lw	a5,-24(s0)
	addi	a5,a5,-1
	sw	a5,-24(s0)
.L2:
  # Evaluación del loop
	lw	a5,-24(s0)
	bgt	a5,zero,.L5
	j	.L4
.L7:
  # escapadita de i==5 con break
	nop # consumimos un ciclo de reloj
.L4:
  # Fin de la función
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```