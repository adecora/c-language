#include <stdio.h>

void main() {
  float input1, input2, answer;
  char opt;
  char more_calculations = 'y'; // MUY IMPORTANTE!!! esta vaina si no está inicializado y hago una división por zero
  // el loop se va a tomar por culo, el continue de división por zero salta a more_calculations == 'y'
  // y la variable tiene mierda. Otra opción un while(1) y evaluar al final if (more_calculations != 'y') break;
  int not_valid, div_by_zero_error;

  do {
    printf("Welcome to the Calculator APP!\n");

    printf("Enter first number: ");
    scanf("%f", &input1);

    printf("Enter second number: ");
    scanf("%f", &input2);

    div_by_zero_error = 0;

    do {

      printf("Enter operation (+, -, *, /): ");
      scanf(" %c", &opt);

      not_valid = 0;
      div_by_zero_error = 0;

      switch (opt) {
        case '+':
          answer = input1 + input2;
          break;
        case '-':
          answer = input1 - input2;
          break;
        case '*':
          answer = input1 * input2;
          break;
        case '/':
          if (input2 == 0) {
            printf("Error, division by zero not allowed.\n");
            div_by_zero_error = 1;
          } else {
            answer = input1 / input2;
          }
          break;
        default:
          printf("Invalid operation.\n");
          not_valid = 1;
      }

    } while (not_valid == 1);

    if (div_by_zero_error == 1) {
      continue;
    }

    printf("Result: %.2f %c %.2f = %.2f\n", input1, opt, input2, answer);

    printf("Would you like to calculate again? (y/n): ");
    scanf(" %c", &more_calculations);

  } while(more_calculations == 'y');

  printf("Thank you for using the Calculator APP. Goodbye!\n");
}