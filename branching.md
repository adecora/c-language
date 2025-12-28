# If - else

Vamos a crear un snippet de `C` para testear el branching `if-else` a nivel de assembly.

```c
void piyush() {
  int i  = 11;
  int j = 2;

  if (i == 10) {
    j = j + 200;
  }

  // Al se una función void hacemos un return vacío
  return;
}
```

Ahora compilamos el código ejecutanto `make piyush`.

```bash
make piyush
# riscv64-unknown-elf-gcc -O0 -ggdb -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld n.s c-asm.c -o main.elf
# riscv64-unknown-elf-objcopy -O binary main.elf main.bin
```

Lanzamos el ejecutable en `qemu` *(para salir de **QEMU** pulsamos `Ctrl-A x`)*.

```bash
make startqemu
# qemu-system-riscv32 -S -M virt -nographic -bios none -kernel main.elf -gdb tcp::1234
```

Y nos conectamos con `gdb`.

```bash
make connectgdb
# gdb-multiarch main.elf -ex "target remote localhost:1234" -ex "break _start" -ex "continue" -q
```

También generamos el código **assembly** para bichearlo, **INPORTANTE!!** recuerda desactivar las optimizaciones (modifica el flag `-O1` por `-O0`) si no el código generado estará será un `ret` ya que nuestra función realmente no hace nada.

```bash
make assembly
#	riscv64-unknown-elf-gcc -O0 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld c-asm.c -S
```

#### gbd

Dentro de **gbd**:

1. Vamos a poner un punto de interrupción en la función `piyush` con `break piyush` o `b piyush`, indica a **gdb** que se pare cada vez que alcancé el bloque de código en donde empieza la función `piyush`.
2. Seguimos con la ejecución normal del programa `continue`, `c`.
3. Seguimos avanzando con `n` o `ni`:
   - Cuando ejecuto `n` se ejecuta una línea de c.
   - Cuando ejecuto `ni` se ejecuta una instrucción.
4. Para salir `quit`, `q`.

#### assembly

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
  # Mueve el sp hacía abajo, está reservando 32 bytes
  # Inicio de stack frame
	addi	sp,sp,-32
  # Guarda el valor original de s0 una word (32bits = 4bytes) en memoria ocupa de sp+28 a sp+31 (justo debajo del sp original)
	sw	s0,28(sp)
  # Suma en s0 el valor de sp + 32bytes que es la posición inicial de sp
  # Final del stack frame
	addi	s0,sp,32
	# Guarda 11 en el registro a5
  li	a5,11
	sw	a5,-20(s0)
	li	a5,2
	sw	a5,-24(s0)
	lw	a4,-20(s0)  # Carga en el registro a4 el valor -20(s0) 11
	li	a5,10  # Carga en el registro a5 10
  # El `if` en el código c es esquivalente a `branch not equal`
	bne	a4,a5,.L4  # Si el registro a4 no es igual a a5 salta a .L4
	lw	a5,-24(s0)
	addi	a5,a5,200
	sw	a5,-24(s0)
	nop
.L4:
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

A la hora de guardar el espacio en el stack frame, este viene determinado porque estamos generand el código sin optimizaciones `-O0` entonces siempre reserva un espacio por convención ABI. Con optimizaciones (`-O1`, `-O2`), el compilador eliminaría el espacio innecesario.

```
s0 (base del frame)
  ↓
  s0-4  a s0-1:   old s0 guardado (4 bytes)
  s0-8  a s0-5:   old ra (si se guardara) (4 bytes)
  s0-12 a s0-9:   otros registros saved (si se usaran)
  s0-20 a s0-17:  variable i (4 bytes)
  s0-24 a s0-21:  variable j (4 bytes)
  s0-28 a s0-25:  (no usado)
  s0-32 a s0-29:  ← ESPACIO para argumentos salientes
                   (outgoing argument area)
```

#### diagrama

Vamos con el diagrama del como se mueve el stack dentro de `piyush`

```
Direcciones altas
       ↑
       │
   ┌───┴──────┐
   │   ...    │
   ├──────────┤ ← s0 = 0x1000 (FINAL/BASE del frame)
   │ old s0   │
   │          │
   │ 32 bytes │ ↑
   │ frame    │ │ El frame de piyush
   │          │ │ ocupa de sp a s0
   │ i = 11   │ │ (de bajo a alto)
   │ j = 2    │ │
   ├──────────┤ ← sp = 0x0FE0 (INICIO/TOPE del frame)
   │   ...    │
       │
       ↓
Direcciones bajas

El «stack crece hacia abajo» si llamamos a otra función, el nuevo **sp** se moverá a direcciones aún más bajas:

Función anterior
s0 anterior → ├──────────┤
              │  piyush  │ ← ocupamos de 0x0FE0 a 0x1000
sp actual  → ├──────────┤ 0x0FE0
              │  nueva   │ ← si llamamos otra función
sp nuevo   → ├──────────┤ 0x0FC0 (más bajo)
```


```
ANTES de entrar a piyush():
                    ┌─────────────┐
                    │   ...       │
                    ├─────────────┤ ← sp = X (ejemplo: 0x1000)
                    │             │


DESPUÉS de: addi sp,sp,-32
                    ┌─────────────┐
                    │   ...       │
                    ├─────────────┤ ← s0 apunta aquí (aún no actualizado)
                    │             │   X (0x1000)
                    │             │
                    │  32 bytes   │
                    │  reservados │
                    │             │
                    ├─────────────┤ ← sp = X-32 (0x0FE0)
                    │             │


DESPUÉS de: sw s0,28(sp) y addi s0,sp,32
                    ┌─────────────┐
                    │   ...       │
                    ├─────────────┤ ← s0 = X (0x1000) [Frame Pointer]
   sp+31 (0x0FFF)   │ s0 guardado │ ← sp+28 a sp+31 (4 bytes)
   sp+28 (0x0FFC)   │  (old s0)   │
                    ├─────────────┤
   sp+24 (0x0FF8)   │             │
                    │             │
                    ├─────────────┤
   sp+20 (0x0FF4)   │             │
                    │             │
                    ├─────────────┤
   sp+16 (0x0FF0)   │             │
                    │             │
                    ├─────────────┤
   sp+12 (0x0FEC)   │             │
                    │             │
                    ├─────────────┤
   sp+8  (0x0FE8)   │             │
                    │             │
                    ├─────────────┤
   sp+4  (0x0FE4)   │             │
                    │             │
                    ├─────────────┤ ← sp = X-32 (0x0FE0)
   sp+0  (0x0FE0)   │             │


CON VARIABLES LOCALES (i y j):
                    ┌─────────────┐
                    │   ...       │
                    ├─────────────┤ ← s0 = X (0x1000)
   s0-8  (0x0FF8)   │ s0 guardado │ ← s0-4 a s0-1 = sp+28 a sp+31
   s0-12 (0x0FF4)   │  (old s0)   │
                    ├─────────────┤
   s0-16 (0x0FF0)   │             │
                    │             │
                    ├─────────────┤
   s0-20 (0x0FEC)   │   i = 11    │ ← sw a5,-20(s0)
                    ├─────────────┤
   s0-24 (0x0FE8)   │   j = 2     │ ← sw a5,-24(s0)
                    ├─────────────┤
   s0-28 (0x0FE4)   │             │
                    │             │
                    ├─────────────┤ ← sp = X-32 (0x0FE0)
   s0-32 (0x0FE0)   │             │
```

---

Modificamos el código original para hacer que la condición dentro del `if` se cumpla.

```c
void piyush() {
  int i  = 10;
  int j = 2;

  if (i == 10) {
    j = j + 200;
  }

  return;
}
```

El código assembly es el mismo que antes, sólo que ahora se carga un 10 en el registro `a5` antes de la instrucción `bne a4,a5,.L4`.

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
	lw	a4,-20(s0)
	li	a5,10
	bne	a4,a5,.L4
	lw	a5,-24(s0)
	addi	a5,a5,200
	sw	a5,-24(s0)
	nop
.L4:
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

---

Modificamos ahora el código para incluir un `else`.

```c
void piyush() {
  int i  = 11;
  int j = 2;

  if (i == 10) {
    j = j + 200;
  } else {
    j = j + 100;
  }

  return;
}
```

El código assembly resultante:

```
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
	li	a5,11
	sw	a5,-20(s0)
	li	a5,2
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	li	a5,10
  # Si a5 y a4 no son iguales entonces salta a .L2 que es el bloque de else
	bne	a4,a5,.L2
  # Si son iguales ejecuta el bloque de `if`
	lw	a5,-24(s0)
	addi	a5,a5,200
	sw	a5,-24(s0)
  # Skipea el código .L2 que es nuestro `else` y se va al final de la función al `return`
	j	.L1
.L2:
	lw	a5,-24(s0)
	addi	a5,a5,100
	sw	a5,-24(s0)
	# nop (No Operation)
	# No hace nada, simplemente consume un ciclo de reloj y avanza el contador del programa a la siguiente instrucción.
	# En RISC-V la psuedo-instrucción `nop` se traduce a `addi x0, x0, 0` (sumar cero al registro cero, que contiene cero).
	# Se usa para:
	#   - Alineación de código: Asegura que ciertas instrucciones esten en direcciones específicas
	#   - Relleno: Espaciar código para optimizaciones de pipeline
	#   - Placeholder: Durante el desarrollo o depuraciñon
	nop
.L1:
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

---

Ahora vamos con multiples `if-else`.

```c
void piyush() {
  int i  = 3;
  int j = 2;

  if (i == 1) {
    j = j + 1;
  } else if (i == 2) {
    j = j + 2;
  } else if (i == 3) {
    j = j + 3;
  } else {
    j = j + 100;
  }

  return;
}
```

Deberiamos tener multiples **branches** en assembly, muchas instrucciones *branch not equal*. Vamos a comprobarlo:

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
	li	a5,3
	sw	a5,-20(s0)
	li	a5,2
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	li	a5,1
  # Si el registro a4 no es igual a a5 (1) salta a .L2
	bne	a4,a5,.L2
  # i == 1
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
	j	.L1
.L2:
	lw	a4,-20(s0)
	li	a5,2
  # Si el registro a4 no es igual a a5 (2) salta a .L4
	bne	a4,a5,.L4
  # i == 2
	lw	a5,-24(s0)
	addi	a5,a5,2
	sw	a5,-24(s0)
	j	.L1
.L4:
	lw	a4,-20(s0)
	li	a5,3
  # Si el registro a4 no es igual a a5 (3) salta a .L5
	bne	a4,a5,.L5
  # i == 3
	lw	a5,-24(s0)
	addi	a5,a5,3
	sw	a5,-24(s0)
	j	.L1
.L5:
  # else
	lw	a5,-24(s0)
	addi	a5,a5,100
	sw	a5,-24(s0)
	nop
.L1:
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```


# Switch-case

Ahora vamos a ver la diferencia del `if-else if-else` *(lo que se conoce como escalera, ladder)* anterior con como se traduce el assembly para el `switch-case`.

```c
void piyush() {
  int i  = 3;
  int j = 2;

  switch (i) {
    case 1:
      j = j + 1;
      break;
    case 2:
      j = j + 2;
      break;
    case 3:
      j = j + 3;
      break;
    default:
      j = j + 100;
      break;
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
	li	a5,3
	sw	a5,-20(s0)
	li	a5,2
	sw	a5,-24(s0)
	lw	a4,-20(s0)
	li	a5,3
	# Primero comprueba si a4 (i) es igual a a5 (3)
	beq	a4,a5,.L2
	lw	a4,-20(s0)
	li	a5,3
	# Aquí comprueba si a4 (i) es > que a5 (3)
	# En ese caso salta a .L3 que es el bloque default
	bgt	a4,a5,.L3
	lw	a4,-20(s0)
	li	a5,1
	# Comprueba si a4 (i) es == que a5 (1)
	beq	a4,a5,.L4
	lw	a4,-20(s0)
	li	a5,2
	# Comprueba si a4 (i) es == que a5 (2)
	beq	a4,a5,.L5
	j	.L3
.L4:
  # case 1
	lw	a5,-24(s0)
	addi	a5,a5,1
	sw	a5,-24(s0)
  # Salta al final de la función al `return`
  # Si comento el `break;` al final del `case 1:` este `j (jump)` desaparecería
	j	.L6
.L5:
	lw	a5,-24(s0)
	addi	a5,a5,2
	sw	a5,-24(s0)
	j	.L6
.L2:
	lw	a5,-24(s0)
	addi	a5,a5,3
	sw	a5,-24(s0)
	j	.L6
.L3:
	lw	a5,-24(s0)
	addi	a5,a5,100
	sw	a5,-24(s0)
	nop
.L6:
	nop
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
	.size	piyush, .-piyush
	.ident	"GCC: (13.2.0-11ubuntu1+12) 13.2.0"
```

La diferencia entre el assembly del `switch` y del `if`.

```diff
--- c-asm.s     2025-12-28 00:37:53.010802312 +0000
+++ tmp 2025-12-28 00:41:28.438789674 +0000
@@ -1,3 +1,4 @@
+#if-else
        .file   "c-asm.c"
        .option nopic
        .attribute arch, "rv32i2p1"
@@ -16,40 +17,34 @@
        li      a5,2
        sw      a5,-24(s0)
        lw      a4,-20(s0)
-       li      a5,3
-       beq     a4,a5,.L2
-       lw      a4,-20(s0)
-       li      a5,3
-       bgt     a4,a5,.L3
-       lw      a4,-20(s0)
        li      a5,1
-       beq     a4,a5,.L4
-       lw      a4,-20(s0)
-       li      a5,2
-       beq     a4,a5,.L5
-       j       .L3
-.L4:
+       bne     a4,a5,.L2
        lw      a5,-24(s0)
        addi    a5,a5,1
        sw      a5,-24(s0)
-       j       .L6
-.L5:
+       j       .L1
+.L2:
+       lw      a4,-20(s0)
+       li      a5,2
+       bne     a4,a5,.L4
        lw      a5,-24(s0)
        addi    a5,a5,2
        sw      a5,-24(s0)
-       j       .L6
-.L2:
+       j       .L1
+.L4:
+       lw      a4,-20(s0)
+       li      a5,3
+       bne     a4,a5,.L5
        lw      a5,-24(s0)
        addi    a5,a5,3
        sw      a5,-24(s0)
-       j       .L6
-.L3:
+       j       .L1
+.L5:
        lw      a5,-24(s0)
        addi    a5,a5,100
        sw      a5,-24(s0)
        nop
-.L6:
-       nop
+.L1:
        lw      s0,28(sp)
        addi    sp,sp,32
        jr      ra
```