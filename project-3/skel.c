#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


// Enum para los tipos de sensores
typedef enum {
  TEMPERATURE,
  HUMIDITY,
  PRESSURE
} SensorType;

// Enum para el status de los sensores
typedef enum {
  ACTIVE,
  INACTIVE,
  ERROR
} SensorStatus;

// Union para las configuraciones especificas y datos
typedef union {
  struct {
    short int min_range; // Temperatura rango mínimo en Celsius
    short int max_range; // Temperatura rango máximo en Celsius
    float reading;       // Última lectura
  } temperature;
  struct {
    float calibration; // Factor de calibración
    float reading;     // Última lectura
  } humidity;
  struct {
    short int altitude; // Compesación de altitud (metros)
    float reading;      // Última lectura
  } pressure;
} SensorData;

// Struct para sensor
typedef struct {
  unsigned char id;
  char name[20];
  SensorType type;
  SensorData data;
  SensorStatus status;
} Sensor;


// Prototipos de las funciones
void init_sensor(Sensor *sensors, unsigned char *count, unsigned char max_sensors);
void read_sensor_data(Sensor *sensors);
void process_sensor_data(Sensor *sensors);
void display_sensor(Sensor *sensors, unsigned char count);


// Main con el uso básico
int main() {
  Sensor sensors[10] = {0}; // Static array, máximo 10 sensores
  unsigned char count = 0;
  char choice;

  // srand: setea el seed para la aleatoriedad de los números
  // time: devuleve en tiempo en segundos desde Epoch, si le pasamos un punter time_t *t_loc, tmbn almancena en t_loc
  srand(time(NULL)); // Seed para las lecturas simuladas

  do {
    printf("\n1. Initialize Sensor\n2. Read Sensor Data\n3. Display Sensors\n4. Exit\n");
    printf("Enter a choice: ");
    scanf(" %c", &choice);

    switch (choice)
    {
      case '1':
        init_sensor(sensors, &count, 10);
        break;

      case '2':
        for (unsigned char i = 0; i < count; i++) {
          read_sensor_data(&sensors[i]);
          process_sensor_data(&sensors[i]);
        }
        break;

      case '3':
        display_sensor(sensors, count);
        break;

      case '4':
        return 0;

      default:
        printf("Invalid choice!\n");
    }
  } while (1);

  return 0;
}



// Implementación de las funciones para completar
void init_sensor(Sensor *sensors, unsigned char *count, unsigned char max_sensors) {
  // TODO: Inicializar el sensor con una configuración del tipo específico
  // TODO: Validar entradas y asegurar count < max_sensors
}

void read_sensor_data(Sensor *sensor) {
  // TODO: Simular la lectura del sensor con valores aleatorios
}

void process_sensor_data(Sensor *sensor) {
  // TODO: Aplicar la lógica de procesado especifica de cada tipo
  // TODO: Actualizar el estado del sensor en función del procesado
}

void display_sensor(Sensor *sensors, unsigned char count) {
  // TODO: Mostrar los detalles del sensor, lecturas y estatus.
}