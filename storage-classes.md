# Storage classes

Tenemos cuatro keywords **(auto, extern, register, static)** conocidas como **storage classes** o también **storage duration**, porque determinan cuanto tiempo existe una variable en memoria durante la ejecución del programa, *ejemplos para bichear en la carpeta [exp](./exp)*.

- **auto:** significa que una variable va estar disponible durante un bloque de código, por ejemplo una función. El scope es dentro de las llaves `{}` donde se ha definido la variable. Si no especificamos nada por defecto una variable se crea como **auto**.
- **register:** es similar a **auto** con la diferencia que el compilador va a trata de alojar esa variable en un registro de la CPU, si es posible **no es mandatorio**.
- **extern:** si tienes una variable que ha sido definida fuera del fichero actual, esa se marca como `extern`, las funciones también pueden marcarse como `extern`. Esto pertenece a **global variables**.
- **static:** actúa sobre la visibilidad de una variable o una función *(un objeto, no confundir con objeto de oop)*.
  * Cuando se usa de forma global fuera de llaves `{}` o de una función, significa que la visibilidad de ese objeto es sólo dentro del fichero actual, no se puede ver fuera de este fichero.
  * Cuando es usa dentro de un bloque `{}` lo que hace es que retiene el valor de la variable durante las llamadas a esa función.

    ```c
    {
      // cada vez que entramos en este bloque el valor de a es 10
      int a = 10;
      a = a + 1;
    }
    ```

    ```c
    {
      // a retiene el valor anterior cada vez que entramos en este bloque, la segunda vez a será 11 y su valor será incrementado a 12
      static int a = 10;
      a = a + 1;
    }
    ```

# void

EL tipo `void` simplemente siginifica ausencia de tipo, por lo tanto no podemos definir una variable como `void a;` porque al no tener tipo, ¿cuantos bytes ocupa esta variable?, ¿qué espacio tenemos que reservar?... sólo hay una expcepción a esto y es que si podemos definir punteros como `void *a;`.