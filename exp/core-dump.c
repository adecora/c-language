// Provocondo el Kaos
// x = 11
// x = 21
// exit
// *** stack smashing detected ***: terminated
// Aborted (core dumped)

// Compilamos con `gcc -ggdb core-dump.c`

// Debuggeamos con `gdb a.out`
// > break main # Punto de ruptura en el main
// > r  # ó run Para arrancar el programa
// > n # ó next Avanza el siguiente statement (instrucción de C). OJO ni ó next instrucción avanza por la instrucciones de emsamblador


// La idea es que el stack se contruya como lo hemos ido defininiendo:

//      ↑ direcciones más altas
//      │
//      │   ┌───────────────┐
//      │   │       3       │   ← otra variable / basura
//      │   ├───────────────┤
//      │   │      12       │   ← y   (pisado)
//      │   ├───────────────┤
//      │   │      21       │   ← int_array[1]
//      │   ├───────────────┤
//      │   │      11       │   ← int_array[0]
//      │   ├───────────────┤
//      │   │      11       │   ← x
//      │   └───────────────┘
//      │
//      ↓ direcciones más bajas

// De forma que si accedemos fuera del stack int_array[3] depende que lo pisamos puede que provoquemos un WTF core dump
// Pero si accedemos a int_array[2] modifiquemos la variable y

// Esa era la teoría porque si vemos que vaina asigno el compilador montó algo así:

// >>> print &x
// $1 = (int *) 0x7fffffffcda8
// >>> print &int_array[0]
// $2 = (int *) 0x7fffffffcdb0
// >>> print &int_array[1]
// $3 = (int *) 0x7fffffffcdb4
// >>> print &y
// $4 = (int *) 0x7fffffffcdac

// No quiere WEA`s por si somos tolays y nos pasamos de frenada accediendo al array

//           ↑ direcciones más altas
//           │
// 0x7fffffffcdb8 │ ┌───────────────┐
//                │ │   (libre)     │
// 0x7fffffffcdb4 │ ├───────────────┤
//                │ │ int_array[1]  │ = 21
// 0x7fffffffcdb0 │ ├───────────────┤
//                │ │ int_array[0]  │ = 11
// 0x7fffffffcdac │ ├───────────────┤
//                │ │       y       │ = 12
// 0x7fffffffcda8 │ ├───────────────┤
//                │ │       x       │ = 11
// 0x7fffffffcda4 │ └───────────────┘
//           │
//           ↓ direcciones más bajas


#include <stdio.h>

int main() {
  int x = 11;
  int int_array[2] = {11, 21};
  int y = 21;

  int_array[3] = 101;

  printf("x = %d\n", x);
  printf("x = %d\n", y);
  printf("exit\n");

  return 0;
}