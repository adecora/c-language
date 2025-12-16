# Este baby program en assembly multiplica dos número mediante un loop.
# Obtenemon la multiplicación de a * b incializando r = 0 y sumando r + a durante b veces

_start:
  # Inicializamos los registros, recordamos que el registro x0 (zero) contiene un 0 hardcoded
  # add inmediate suma dos registros más el número indicado
  addi x1, x0, 2
  addi x2, x0, 5
  addi x3, x0, 0

repeat_addition:
  # En x3 almacena el resultado sumando x1 durante x2 veces
  add x3, x3, x1
  addi x2, x2, -1 # Para restar hacemos un add inmediate de -1
  bne x2, x0, repeat_addition # Si el x2 no es igual a 0 volvemos al loop de multiplicación

j . # Salta al mismo punto, loop infinito
