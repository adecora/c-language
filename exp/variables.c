#include <stdio.h>

// Como la función está definida despues que sea usada, tenemos que declararla antes para que el compilador no se queje
void _567();  // forward declaration of function, una función de este return type con este nombre y que recibe estos parámetros existe
             // no porculees si se usa y aun se declaró porque vas a encontrar la declaración luego

void main() {
  _567();
}

void _567() {
  // Aunque if es uns palabra reservada que no puede usarse como nombre de variable _if si es un nombre que cumple las convenciones
  int _if = 103;

  printf("%d\n", _if);
}