# Project 2: Generating Digital Audio

Generate a C program that generates a **sine wave-a fundamental** audio signal-and saves it as a **raw PCM *(Pulse Code Modulation)*** data in a file.

The output will be a `.raw` file containing uncompressed audio samples, which can later ber imported into audio software (e.g Audacity) as **PCM data** for playback.

> This project simulates how digital audio is created and stored, offering hands-on experience with signal generation and file I/O in C.


## Objectives

- Generate a sine wave with customizable frequency, amplitude, and duration.
- Encode the sine wave as PCM data using specified sample rate and bit depth.
- Write the PCM data to a file in a raw format.
- Explore key C programming concpts through practical application.


## Project Features

- User Input: Accept parameters like frequency (e.g., 440 Hz for an A note), duration (in seconds), and amplitude (volume level).
- Sine Wave Generation: Use the `sin()` function from the *math library* to compute sine wave samples.
- PCM Encoding: Convert the sine wave into **16-bit PCM** samples (signed integers).
- File Output: Save the PCM data to a `.raw` file, which can be played back with proper audio tools.
- Basic Error Handling: Check for file creation issues and invalid user inputs.


## Implementation Steps

1. Setup: Include all necessary headers *(stdio.h, stdlib.h, math.h)* and define constants (e.g., sample rat=44_100Hz, bit depth=16).
2. Input Handling: Use `scanf()` to get frequency, duration, and amplitude from the user.
3. Sine Wave Calculation: Compute samples ussing the formula: `sample = amplitude * sin(2 * PI * frequency * t/ sample_rate)`, where `t` is the sample index.
4. PCM conversion: Scale the floating-point sine values **(-1.0 to 1.0)** to 16-bit integers **(-32_768 to 32_767)**.
5. File Writing: Open a file in binary mode `fopen("output.raw", "wb")` and write the samples using fwrite().
6. Cleanup: Close the file and handle any errors.


### Sample Output

- A 440Hz sine wave for 5 seconds at 44.1 kHz sample rate will produce a 441_000 byte file (44_100 samples/sec * 5 sec * 2bytes/sample for 16-bit mono).
- Import the `.raw` file into Audacity *(File > Import > Raw Data, 44.1 kHz, 16-bit PCM, mono) to hear the tone.


## Tips

1. Basic I/O operations
  * `printf()` and `scanf()` for user interaction.
  * Understand formatted input/output, including how to read and validate user inputs (e.g., ensuring frequncy is positive).

2.  Mathematical Functions
    * Use of `math.h` library and `sin()` function.
    * Link the *math library* (**-lm** flag on during compilation) and apply trigonometic functions to real.world problems like signal generation.

3. Data Types ans Casting
  * Convertion between `double` (sine wave values) and `int16_t` (PCM samples).
  * Learn about type casting, integer overflow, and and importance of choosing appropriate data types (e.g., `int16_t` from `stdint.h` for 16-bit audio).

4. Loops and Iteration
  * `for` loop to generate samples over time.
  * Practice loop control and iteration to process large datasets (e.g., 44_100 samples per second).

5. File Handling
  * `fopen()`, `fwrite()`, `fclose()` for binary file operations.
  * Master binary file I/O, understand the difference between text and binary modes, and handle file pointers.

6. Pointers and Memory Management
  * Use pointers with `fwrite()` to write sample data.
  * Gain familiarity with pointers, memory addresing, adn passing data to functions efficiently.

7. Error Handling
  * Check return values of `fopen()`, `fwrite()`for NULL or failure.
  * Implement basic error checking and use conditional statements (if) to manage program flow.

8. Constants and Preprocessor Directives
  * `#define` for constants like `SAMPLE_RATE` and `PI`.
  * Use the preprocessor to make code more readable and maintainable.

9. Arrays (Optional Extension)
  * Store samples in an array before writing to a file.
  * Practice dynamic memory allocation `malloc()`, `free()`and array manipulation.

10. Modularity (Optional Extension)
  * Split code into functions `genetate_sine()`, `write_pcm()`.
  * Understand function declarations, prototypes, and passing parameters by value or reference.


## Compile and Run

- compile: `gcc main.c -lm`
- run: `./a.out`
- play: `Import in Audacity and play`


## Learning Extensions

- Stero Output: Modify the program to write two channels (left and right).
- Multiple Frequencies: Generate a chord by summing multiple sine waves.
- WAV Header: Add a WAV file header to make the output playable wihout importing as raw data.