# volatile keyword

Para conocer que hace la **keyword** **volatile** primero vamos a compilar una pequeña función:

```c
int piyush() {

  int i = 10;

  i = i + 1;
  i = i + 10;

  return 0;
}
```

Este es código que obtenemos del compilador, **pero tenemos que tener en cuenta que las optimizaciones del compilador están desactivadas**.

```assembly
piyush:
	addi	sp,sp,-32
	sw	s0,28(sp)
	addi	s0,sp,32
	li	a5,10       # Suma 10 al registro a5
	sw	a5,-20(s0)  # Guarda el registro en el stack de la función
	lw	a5,-20(s0)  # Carga el valor del stack en el registro
	addi	a5,a5,1   # Suma uno al registro
	sw	a5,-20(s0)  # Guarda el registro en el stack de la función
	lw	a5,-20(s0)  # Carga el valor del stack en el registro
	addi	a5,a5,10  # Suma uno al registro
	sw	a5,-20(s0)  # Guarda el valor en el registro
	li	a5,0
	mv	a0,a5
	lw	s0,28(sp)
	addi	sp,sp,32
	jr	ra
```

Si activamos las optimizaciones del compilador, moviendo el flag **-O0** por **-O1**.

```bash
riscv64-unknown-elf-gcc -O1 -nostdlib -march=rv32i -mabi=ilp32 -Wl,-Tm.ld c-asm.c -S
```

```assembly
piyush:
	li	a0,0
	ret
```

**Qué ha pasado???** El compilador detecta que la variable `i` es purria, no se está utilizando en ningún lugar y simplemmente pasa de generar de su código, simplemente mueve el valor del **return**, **0** al registro **a0** y luego hace el **ret** para volver a la posición después de la llamada a la función.


**Y si usamos el valor de `i` como `return`?**

```c
int piyush() {

  int i = 10;

  i = i + 1;
  i = i + 10;

  return i;
}
```

El compilador sigue siendo más listo que nosotros, comprueba que el valor final de `i` es **21**, no pierde **ciclos de CPU** con los pasos intermedios porque no aportan nada, simplemente pasa el valor final **21** a registro **a0** y hace el **ret**.

```assembly
piyush:
	li	a0,21
	ret
```

Ahora es cuando podemos declarar `i` como **volatile** y ver que pasa.

```c
int piyush() {

  volatile int i = 10;

  i = i + 1;
  i = i + 10;

  return i;
}
```

```assembly
piyush:
	addi	sp,sp,-16
	li	a5,10
	sw	a5,12(sp)
	lw	a5,12(sp)
	addi	a5,a5,1
	sw	a5,12(sp)
	lw	a5,12(sp)
	addi	a5,a5,10
	sw	a5,12(sp)
	lw	a0,12(sp)
	addi	sp,sp,16
	jr	ra
```

Al declarar `i` como **volatile** le estamos indicando al compilador que no optimice la variable `i`. Lo cualo ser lo que pasa entonces? Volvemos a `assembly` equivalente al del principio sin optimiza, donde se realiza la operación en el registro, y luego se guarda en el stack de la función... de vuelta a otra operación se trae el valor del stack al registro, se realiza la nueva operación en este y se vuelve a guardar en el stack de la función.

> 👁️
> Lo que realmente significa **volatile** es que el valor de la variable `i` no va a ser cacheado en el registro de la CPU, se va a enviar fuera de la CPU.