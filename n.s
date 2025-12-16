# Generamos un programa para ejecutar la función `piyush` del fichero `c-asm.c`
_start:
  # Inicializamos el sp (stack pointer) 2kb sobre el inicio de la memoria
  li sp,  0x80002000
  # Necesitamos usar `jal` que significa salta a `piyush` pero además guarda la dirección de retorno,
  # la dirección de la próxima instrucción, en el registro `ra`
  jal piyush
j .
