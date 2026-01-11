// Compilamos con `gcc -ggdb char-array.c`
// Debuggeamos con `gdb a.out`
// > break main # Punto de ruptura en el main
// > r  # ó run Para arrancar el programa
// > n # ó next Avanza el siguiente statement (instrucción de C). OJO ni ó next instrucción avanza por la instrucciones de emsamblador

// Da la causalidad que cuando terminamos de setear el array de caracteres, s[10] que está fuera de la memoria definida es un caracter nulo
// dando la apriencia que se imprime bien el string y esta todo OK pero nanay eso es garbage (una puto mojón) y el caracter nulo está de casulidad
//    >>> p
//    $2 = "ABCDEFGHIJ"
//    >>> p s[10]
//    $3 = 0 '\000'
//    >>> p s[11]
//    $4 = -93 '\243'
//    >>> p s[12]
//    $5 = -87 '\251'

// Para no comernos todo el bucle de inicialización intrucción a instrucción
// >>> break char-array.c:43 // ó b 43 Pone un punto de ruptura en la línea 43 del fichero
// Breakpoint 2 at 0x5555555551da: file char-array.c, line 43.
// >>> c // ó continue Continua hasta el breakpoint

// Lo normal que podrí pasar es lo siguiente, que ese caracter no sea el nulo, lo formzamos seteandolo nosotros
//    >>> set var s[10] = 'w'
//    >>> p s[10]
//    $7 = 119 'w'

// Y al continuar la ejecución del programa, la salida es esta vaina
// Nuestro array es: «ABCDEFGHIJw��\1��@`����»  Ahora ya estamos seguros que algo l'hemos liao

#include <stdio.h>

int main() {
  // Si lo inicializo me puedo fumar el declarar explicitamente el size del array `char x[3] = ...`
  char x[] = {'H', 'i', '!'};

  // Sin fliparse, sin declaración si tenemos que indicar el tamaño
  char s[10];

  printf("Size of x: %ld\n", sizeof(x));
  printf("Szie of s: %ld\n", sizeof(s));

  // Snippet para inicializar el array de caracteres
  int i = 0;
  while (i<10) {
    s[i] = 65 + i;  // Esta vaina es lo mismo que `s[i] = 'A' + i;`

    printf("s[%d] = %c\n", i, s[i]);

    i = i + 1;
  }

  // No flipes este array de caracteres todavía no puedes imprimirlo como un string, quieres un Overflow de manual
  // OJO tenemos que indicarle a C dnd termina nuestro string con un caracter nulo '\0'
  printf("Nuestro array es: «%s»\n", s);

  // Esta troita xa está lista para entender que s no es sólo un array de char sino un String
  s[9] = '\0';
  printf("Nuestro array es: «%s»\n", s);


  // Podemos inicializa un array de caracateres para que sea tratado como un String tal que y nos olvidamos de toda la vaina de antes
  char y[] = "Hi!";

  printf("Size of y: %ld\n", sizeof(y));
  printf("Caracter array inicializado como string es: «%s»\n", y);


  return 0;
}