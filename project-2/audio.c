// cc -o main audio.c -lm && ./main

// ffplay -nodisp -autoexit -f s16le -ar 44100  -i audio.raw
//   • -nodisp: Reproduce sin lanzar el display
//   • -autoexit: Cuando termina la reproducción control vuelve a la consola
//   • -f s16le: Formato (s16le = signed 16-bit little-endian PCM)
//               Otros: s16be, s8, u8, s24le, s32le, f32le, etc
//   • -ar 44100: Sample rate (frecuencia de muestreo en Hz)
//                Común: 8000, 16000, 22050, 44100, 48000
//   • -i input.raw: Archivo de entrada

// ffplay -nodisp -autoexit audio.wav

// Normalizar seno a 16 bits sin signo
//
// La salida del seno [-1, 1]
// Un entero sin signo [0 , 65535]
// Norm: [-1, 1].. [0, 2].. [0, 1].. [0, 65535]
// uint16 = ((sin(X) + 1) / 2) x 65535
//   • sin(X) = -1  →  0      |
//   • sin(X) =  0  →  32767  | <- Esta vaina no vale para señales de audio
//   • sin(X) = +1  →  65535  |

// Para audio tenemos que normaliza seno a 16 bits con signo
// La salida del seno [-1, 1]
// Un entero con signo [-32768, 32767]
// int16_t = sin(X) x 32767 <- Nunca se llega al valor -32768, pero no problem

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h> // trae el int16_t
#include <math.h>
#include <errno.h>

#define SAMPLE_RATE 44100
#define MAX_INT16_VALUE 32767

// WAV header - 44 bytes
typedef struct {
  char file_type[4];   // «RIFF»
  uint32_t file_size;  // Tamaño del fichero - 8 bytes
  char file_format[4]; // Formato «WAVE»

  // [Chunk describing the data format]
  char fmt_id[4];           // «fmt »
  uint32_t block_size;      // Tamaño del subchunk fmt (16 para PCM)
  uint16_t audio_format;    // Formato de audio (1 = PCM integer, 3 = IEEE 754 float)
  uint16_t num_channels;     // Número de canales
  uint32_t sample_rate;     // Frecuencia de muestreo en Hz (44100)
  uint32_t byte_rate;       // sample_rate * num_channels * bits_per_sample/8
  uint16_t block_align;     // num_channels * bits_per_sample/8
  uint16_t bits_per_sample; // Bits por sample = 16 bits

  // [Chunk containing the sampled data]
  char data_id[4];    //  «data»
  uint32_t data_size; // Tamaño de los datos de audio
} WAVHeader;

void write_wav_header(FILE *fp, int num_samples, int num_channels) {
  WAVHeader header;

  // RIFF header
  memcpy(header.file_type, "RIFF", 4);
  header.file_size = 36 + num_samples * num_channels * sizeof(int16_t);
  memcpy(header.file_format, "WAVE", 4);

  // [Chunk describing the data format]
  memcpy(header.fmt_id, "fmt ", 4);
  header.block_size = 16;
  header.audio_format = 1;
  header.num_channels = num_channels;
  header.sample_rate = SAMPLE_RATE;
  header.bits_per_sample = 16;
  header.byte_rate = SAMPLE_RATE * num_channels * header.bits_per_sample / 8;
  header.block_align = num_channels * header.bits_per_sample / 8;

  // [Chunk containing the sampled data]
  memcpy(header.data_id, "data", 4);
  header.data_size = num_samples * num_channels * sizeof(int16_t);

  fwrite(&header, sizeof(WAVHeader), 1, fp);
}

void clean_input_buffer(void) {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int read_int(const char *message, int min, int max) {
  int value;
  int result;

  while(1) {
    printf("%s", message);
    result = scanf("%d", &value);

    if (result !=1) {
      printf("Error: you must introduce an integer value.\n");
      clean_input_buffer();
      continue;
    }

    if (value < min || value > max) {
      printf("Error: value must be betweeen «%d» and «%d».\n", min, max);
      clean_input_buffer();
      continue;
    }

    clean_input_buffer();

    return value;
  }
}

int main() {
  char filename[] = "audio.wav";
  int amplitude;
  int tone_frequency;
  int duration;
  int num_channels;

  printf("Welcome to generate your digital audio tone!\n");

  num_channels = read_int("Select number of channels (1=mono, 2=stereo): ", 1, 2);
  tone_frequency = read_int("What frequency note you want to generate [e.g. 440Hz]: ", 20, 20000);
  duration = read_int("Introduce the duration of the note (in seconds): ", 1, 120);
  amplitude = read_int("Select the volumen level [range from 0 to 100]: ", 0, 100);

  float *sine_array_left;
  float *sine_array_right = NULL;
  int16_t *audio_array;
  int num_samples = SAMPLE_RATE * duration;


  if ((sine_array_left = (float *) malloc(num_samples * sizeof(float))) == NULL) {
    perror("Not enough memory to allocate.\n");
    return EXIT_FAILURE;
  }

  if (num_channels == 2) {
    if ((sine_array_right = (float *) malloc(num_samples * sizeof(float))) == NULL) {
      perror("Not enough memory to allocate.\n");
      free(sine_array_left);
      return EXIT_FAILURE;
    }
  }

  if ((audio_array = (int16_t *) malloc(num_samples * num_channels * sizeof(int16_t))) == NULL) {
    perror("Not enough memory to allocate.\n");
    free(sine_array_left);
    if (sine_array_right) free(sine_array_right);
    return EXIT_FAILURE;
  }


  FILE *fp = fopen(filename, "wb");
  if (!fp) {
      fprintf(stderr, "Error when open %s: %s\n", filename, strerror(errno));
      free(sine_array_left);
      if (sine_array_right) free(sine_array_right);
      free(audio_array);
      return EXIT_FAILURE;
  }

  for (int s = 0; s < num_samples; ++s) {
    // Cada ciclo completo del seno: 2 * pi radianes
    // Un tono de 'tone_frequency' Hz -> Número de ciclos que completa por segundo
    // Cada muestra respresenta un instante de tiempo `t=s/SAMPLE_RATE (segundos)`

    // La fase (ángulo) del seno en la muestra s

    float sine_left = sin(2 * M_PI * tone_frequency * ((float) s / SAMPLE_RATE)) * ((float) amplitude / 100.0);
    sine_array_left[s] = sine_left;

    if (num_channels == 1) {
      // Mono
      audio_array[s] = sine_left * MAX_INT16_VALUE;
    } else {
      // Estereo

      float sine_right = sin(2 * M_PI * (tone_frequency + 4) * ((float) s / SAMPLE_RATE)) * ((float) amplitude / 100.0);
      sine_array_right[s] = sine_right;

      // Intercalamos canal izquierdo y canal derecho
      audio_array[s * 2] = sine_left * MAX_INT16_VALUE;
      audio_array[s * 2 + 1] = sine_right * MAX_INT16_VALUE;
    }
  }

  // Para poder reproducir los resultados
  srand(1337);

  // Generar número aleatorio entre N y M (inclusive)
  // N + rand() % (M - N + 1);
  int i = rand() % ((num_samples - 10) + 1);

  printf("\nSample values preview:\n");
  printf("======================\n");
  for (int j = 0; j < 10; ++j) {
    if (num_channels == 1) {
      printf("Sample: %6d: sine=%.5f, audio=%6d\n",
        i + j, sine_array_left[i + j], audio_array[i + j]);
      } else {
        printf("Sample: %6d: sine_L=%.5f, audio_L=%6d, sine_R=%.5f, audio_R=%6d\n",
          i + j, sine_array_left[i + j], audio_array[(i + j) * 2], sine_array_right[i + j], audio_array[(i + j) * 2 + 1]);
    }
  }

  // Escribir el header WAV
  write_wav_header(fp, num_samples, num_channels);

  for (int s = 0; s < (num_samples * num_channels); ++s) {
    // Escribimos al fichero datos del audio
    size_t written = fwrite(&audio_array[s], sizeof(int16_t), 1, fp);
    if (written != 1) {
        perror("Error when trying to write on file\n");
        fclose(fp);
        free(sine_array_left);
        if (sine_array_right) free(sine_array_right);
        free(audio_array);
        return EXIT_FAILURE;
    }
  }

  printf("\nGenerated %s audio file «%s» with %ld bytes (header + data)\n",
    num_channels == 1 ? "MONO" : "STEREO",
    filename,
    sizeof(WAVHeader) + num_samples * num_channels * sizeof(int16_t));

  fclose(fp);
  free(sine_array_left);
  if (sine_array_right) free(sine_array_right);
  free(audio_array);

  return 0;
}