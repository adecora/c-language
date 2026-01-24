// cc -o main embbeded.c && ./main
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <float.h>

#define MAX_SENSORS 10
#define read_short_int(msg, ...) read_short_int_impl(msg, ##__VA_ARGS__, SHRT_MIN, SHRT_MAX)
#define read_float(msg, ...) read_float_impl(msg, ##__VA_ARGS__, FLT_MIN, FLT_MAX)
// Como rulan las macros para definir parámetros por defecto
// #define MACRO(a, ...) func(a, ##__VA_ARGS__)
// ##__VA_ARGS__ -> operador especial del preprocesador
//     • __VA_ARGS__ captura todos los argumentos en ...
//     • ## concatena los argumentos con coma, si no argumentos se fuma la coma anterior
// MACRO(1)        → func(1)       // La coma se elimina
// MACRO(1, 2)     → func(1, 2)    // La coma se mantiene
// MACRO(1, 2, 3)  → func(1, 2, 3) // La coma se mantiene


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
// ¿?¿? Cual es la movida con esta vaina ¿?¿?
// Dependiendo del tipo de sensor sólo vamos a estar tocando un tipo de datos si lo creamos como struct
//
//  struct: |← 8 bytes →|← 8 bytes →|← 6 bytes →| = 24 bytes (22 bytes + extra padding por movidas)
//                                                  podemos bichear sin el padding con __attribute__((packed)) al final de la declaración del struct
//                                                  es una orden al compilador para que empaquete la estructura lo más compacta posible
//                                                  SIN packed
//                                                  struct {
//                                                      short int altitude;   // offset 0-1   (2 bytes)
//                                                      // [PADDING: 2 bytes]  // offset 2-3
//                                                      float reading;        // offset 4-7   (4 bytes)
//                                                  } pressure;
//                                                  // Total: 8 bytes
//
//                                                  // CON packed
//                                                  struct {
//                                                      short int altitude;   // offset 0-1   (2 bytes)
//                                                      float reading;        // offset 2-5   (4 bytes)
//                                                  } pressure __attribute__((packed));
//                                                  Total: 6 bytes
//
//                                                  ¿¿?Why padding¿¿?
//                                                  Los procesadores modernos acceden a la memoria en words de tamaño fijo, 4 o 8 bytes típicamente
//                                                  Acceder a los datos alineados es más eficiente:
//                                                  Usa un ciclo de CPU, una sola operación de lectura
//
//                                                  Alineación típica en arquitecturas de 64 bits:
//                                                  char      → 1 byte  (puede estar en cualquier dirección)
//                                                  short int → 2 bytes (dirección múltiplo de 2)
//                                                  int       → 4 bytes (dirección múltiplo de 4)
//                                                  float     → 4 bytes (dirección múltiplo de 4)
//                                                  double    → 8 bytes (dirección múltiplo de 8)
//
//                                                  struct {
//                                                      // temperature
//                                                      short int min_range;  // offset 0-1   (2 bytes)
//                                                      short int max_range;  // offset 2-3   (2 bytes)
//                                                      float reading;        // offset 4-7   (4 bytes)
//
//                                                      // humidity
//                                                      float calibration;    // offset 8-11  (4 bytes)
//                                                      float reading;        // offset 12-15 (4 bytes)
//
//                                                      // pressure
//                                                      short int altitude;   // offset 16-17 (2 bytes)
//                                                      // [PADDING: 2 bytes]  // offset 18-19
//                                                      float reading;        // offset 20-23 (4 bytes)
//
//                                                      // Total: 24 bytes
//                                                  }
//   union: |←  8 bytes  →|
//          |←  8 bytes  →|  =  8 bytes
//            |← 6 bytes →|

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

// Auxiliares
void clean_input_buffer();
void read_common_info(Sensor *sensor);
unsigned char read_sensor_id(const char *message);
void read_sensor_name(const char *message, char *name, int max_len);
short int read_short_int_impl(const char *message, short int min, short int max);
float read_float_impl(const char *message, float min, float max);


// Main con el uso básico
int main() {
  Sensor sensors[MAX_SENSORS] = {0}; // Static array, máximo MAX_SENSORS sensores
  unsigned char count = 0;
  char choice;

  // srand: setea el seed para la aleatoriedad de los números
  // time: devuleve en tiempo en segundos desde Epoch, si le pasamos un punter time_t *t_loc, tmbn almancena en t_loc
  srand(time(NULL)); // Seed para las lecturas simuladas

  // inifinity loop
  for(;;) {
    system("clear"); // Limpia la pantalla al inicio del loop
    printf("\n=== SENSOR MANAGEMENT SYSTEM ===\n");
    printf("1. Initialize Sensor\n2. Read Sensor Data\n3. Display Sensors\n4. Exit\n");
    printf("Enter a choice: ");
    scanf(" %c", &choice);
    clean_input_buffer();  // buffer limpicito post-lectura

    switch (choice)
    {
      case '1':
        init_sensor(sensors, &count, MAX_SENSORS);
        break;

      case '2':
        for (unsigned char i = 0; i < count; i++) {
          read_sensor_data(&sensors[i]);
          process_sensor_data(&sensors[i]);
        }
        printf("Sensor's lectures and processing updated!!!\n");
        printf("Press Enter to continue...");
        getchar();
        break;

      case '3':
        display_sensor(sensors, count);
        break;

      case '4':
        return 0;

      default:
        printf("Invalid choice! Select one on range 1-4.\n");
        printf("Press Enter to continue...");
        // Dos getchar()¿?¿? scanf() deja al caracter de nueva línea en el buffer de entrada cuando escribimos una opción, p.ej.:
        // '1' '\n' el primero consume el enter abandonaico por scanf el segundo espera nueva entrada
        // getchar(); getchar();
        // scanf("%*c"); se usa para limpiar el buffer consume una entrada y descarta, no más chupa un caracter
        // while (getchar() != '\n');
        getchar();
    }
  };

  return 0;
}



// Implementación de las funciones para completar
void init_sensor(Sensor *sensors, unsigned char *count, unsigned char max_sensors) {
  // TODO: Inicializar el sensor con una configuración del tipo específico
  // TODO: Validar entradas y asegurar count < max_sensors
  if (*count >= MAX_SENSORS) {
    printf("\nNo slots availables to add more sensors!\n");
    printf("Press Enter to continue...");
    // Waiting por que el usuario decida continuar, break time para que vea el mensaje
    getchar();
    return;
  }

  Sensor sensor;
  char sensor_type;

  do {
    system("clear");
    printf("\nChoose the sensor you want to add\n• Temperature (t)\n• Humidity (h)\n• Pressure (p)\n");
    printf("Enter your choice: ");
    scanf(" %c", &sensor_type);
    clean_input_buffer();

    switch (sensor_type)
    {
      case 't':
      case 'T':
        printf("Temperature sensor:\n");
        printf("===================\n");
        sensor.type = TEMPERATURE;
        read_common_info(&sensor);
        sensor.data.temperature.min_range = read_short_int("Introduce sensor min range temperature in Celsius: ");
        sensor.data.temperature.max_range = read_short_int_impl("Introduce sensor max range temperature in Celsius: ", sensor.data.temperature.min_range, SHRT_MAX);
        break;

      case 'h':
      case 'H':
        printf("Humidity sensor\n");
        printf("===============\n");
        sensor.type = HUMIDITY;
        read_common_info(&sensor);
        sensor.data.humidity.calibration = read_float_impl("Introduce sensor calibration: ", 0.0, 1.0);
        break;

        case 'p':
        case 'P':
        printf("Pressure sensor\n");
        printf("===============\n");
        sensor.type = PRESSURE;
        read_common_info(&sensor);
        sensor.data.pressure.altitude = read_short_int("Introduce sensor altitude: ");
        break;

      default:
        printf("Invalid choice! There is no %c sensor\n", sensor_type);
        printf("Press Enter to continue...");
        getchar();
        // Vuelta p'trás, mientras opción no valida repetimos el do-while
        continue;
    }
    // Si opción válida breakeamos el loop
    break;
  } while(1);

  sensor.status = INACTIVE;
  sensors[(*count)++] = sensor;
}

void read_sensor_data(Sensor *sensor) {
  // TODO: Simular la lectura del sensor con valores aleatorios
  switch(sensor->type) {
    case TEMPERATURE:
      const int GAP = 5;
      // La temperature se aleatoriza entre un +- GAP de los valores mínimo y máximo del sensor
      // Remembering  rand() devuelve entero, pasamos a flotante
      float temperature = ((double)rand()/RAND_MAX *
        (sensor->data.temperature.max_range - sensor->data.temperature.min_range + GAP))
        + sensor->data.temperature.min_range - GAP;
      sensor->data.temperature.reading = temperature;
      break;
    case HUMIDITY:
      // Aleatorio entre 0 y 100
      // Entre 0 y 100 si fuera entrero puedo trampearlo con el modulo rand() % 101
      float humidity = (double)rand()/RAND_MAX * 100;
      sensor->data.humidity.reading = humidity;
      break;
    case PRESSURE:
      // Aleatorio entre 20 y 50
      float pressure = 20 + ((double)rand() / RAND_MAX) * 30;
      sensor->data.pressure.reading = pressure;
      break;
    default:
      fprintf(stderr, "Error, unkown type %d.\n", sensor->type);
      exit(1);
  }
}

void process_sensor_data(Sensor *sensor) {
  // TODO: Aplicar la lógica de procesado especifica de cada tipo
  // TODO: Actualizar el estado del sensor en función del procesado
    switch(sensor->type) {
    case TEMPERATURE:
      if (sensor->data.temperature.reading < sensor->data.temperature.min_range ||
          sensor->data.temperature.reading > sensor->data.temperature.max_range) {
        sensor->status = ERROR;
      } else {
        sensor->status = ACTIVE;
      }
      break;
    case HUMIDITY:
      sensor->data.humidity.reading *= sensor->data.humidity.calibration;
      sensor->status = ACTIVE;
      break;
    case PRESSURE:
      // Total invetion: -0.12 hPa por metro de altitud
      sensor->data.pressure.reading -= (sensor->data.pressure.altitude * 0.12f);
      sensor->status = ACTIVE;
      break;
    default:
      fprintf(stderr, "Error, unkown type %d.\n", sensor->type);
      exit(1);
  }

}

void display_sensor(Sensor *sensors, unsigned char count) {
  // TODO: Mostrar los detalles del sensor, lecturas y estatus.
  if (count == 0) {
    printf("There is no sensors on the system.\n");
    printf("Press Enter to continue...");
    getchar();
    return;
  }

  // Clean screen for us
  system("clear");

  printf("\nThere is %d sensors on the system, ", count);
  if (count < MAX_SENSORS) printf("still %d slots available.\n\n", MAX_SENSORS - count);
  else printf("no more slots available.\n\n");

  for (int i = 0; i < count; ++i) {
    // TODO: Esta vaina copia toda la estructura, duplicamos memory
    // Usar: Sensor *sensor = &sensor[i];
    Sensor sensor = sensors[i];

    switch(sensor.type) {
      case TEMPERATURE:
        printf("Temperature sensor \"%s\" (id: %hhu):\n", sensor.name, sensor.id);
        printf("\t• status: %s\n", sensor_status_to_string(sensor.status));
        if (sensor.status == INACTIVE) break;
        printf("\t• temperature [%hd - %hd]: %.2fºC\n",
          sensor.data.temperature.min_range,
          sensor.data.temperature.max_range,
          sensor.data.temperature.reading);
          break;
      case HUMIDITY:
        printf("Humidity sensor \"%s\" (id: %hhu):\n", sensor.name, sensor.id);
        printf("\t• status: %s\n", sensor_status_to_string(sensor.status));
        if (sensor.status == INACTIVE) break;
        printf("\t• humidity (cal: %.2f): %.2f%%\n",
          sensor.data.humidity.calibration,
          sensor.data.humidity.reading);
        break;
      case PRESSURE:
        printf("Pressure sensor \"%s\" (id: %hhu):\n", sensor.name, sensor.id);
        printf("\t• status: %s\n", sensor_status_to_string(sensor.status));
        if (sensor.status == INACTIVE) break;
        printf("\t• pressure (alt: %hd m): %.2fbar\n",
          sensor.data.pressure.altitude,
          sensor.data.pressure.reading);
        break;
      default:
        fprintf(stderr, "Error, unkown type %d.\n", sensor.type);
        exit(1);
    }

    printf("\n");
  }

  // Stopeamos al final para visualizar los sensores
  printf("Press Enter to continue...");
  getchar();
}


// Auxiliares
const char* sensor_status_to_string(SensorStatus status) {
  switch(status) {
    case ACTIVE: return "ACTIVE";
    case INACTIVE: return "INACTIVE";
    case ERROR: return "ERROR";
    default: return "UNKNOWN";
  }
}

void clean_input_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void read_common_info(Sensor *sensor) {
  sensor->id = read_sensor_id("Introduce sensor id: ");
  read_sensor_name("Introduce sensor's name: ", sensor->name, 20);
}

unsigned char read_sensor_id(const char *message) {
  unsigned char sensor_id;
  int result;

  for(;;) {
    printf("%s", message);
    result = scanf(" %hhu", &sensor_id); // remembering el espacio al principio

    if (result != 1) {
      printf("Error: you must introduce an unsigned char value.\n");
      clean_input_buffer();
      continue;
    }

    clean_input_buffer();
    return sensor_id;
  }
}

void read_sensor_name(const char *message, char *name, int max_len) {
  do {
    printf("%s", message);

    if (fgets(name, max_len, stdin) != NULL) {
      size_t len = strlen(name);

      // nos fumamos el Enter del teclado para añadir el caracter fin de cadena
      if (len > 0 && name[len -1] == '\n') {
        name[len - 1] = '\0';
      }

      if (strlen(name) == 0) {
        printf("Error: name cannot be empty. Please try again.\n");
      }
    } else {
      name[0] = '\0';
      printf("Error: failed to read input.\n");
    }
  } while(!strlen(name)); // loopea mientras no tengamos un nombre (len > zero)
}

short int read_short_int_impl(const char *message, short int min, short int max) {
  short int value;
  int result;

  for (;;) {
    printf("%s", message);
    result = scanf(" %hd", &value);

    if (result != 1) {
      printf("Error: you must introduce a short int value.\n");
      clean_input_buffer();
      continue;
    }

    if (value < min || value > max) {
      printf("Error: value must be between %hd and %hd.\n", min, max);
      clean_input_buffer();
      continue;
    }

    clean_input_buffer();
    return value;
  }
}

float read_float_impl(const char *message, float min, float max) {
  float value;
  int result;

  for (;;) {
    printf("%s", message);
    result = scanf(" %f", &value);

    if (result != 1) {
      printf("Error: you must introduce a float value.\n");
      clean_input_buffer();
      continue;
    }

    if (value < min || value > max) {
      printf("Error: value must be between %.4f and %.4f.\n", min, max);
      clean_input_buffer();
      continue;
    }

    clean_input_buffer();
    return value;
  }
}
