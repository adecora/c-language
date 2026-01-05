# Project 1: Calculator

## Program Overview

The calculator program will:

1. Prompt the user to enter two numbers.
2. Ask the user to select an operation (e.g., +, -, *, /).
3. Perform the requested calculation and display the result.
4. Handle basic error cases (e.g., division by zero).
5. Optionally, allow the user to perform multiple calculations in a loop.


## Design Considerations

- User-Friendly: Clear prompts and outputs for ease of use.
- Error Handling: Prevent division by zero errors.
- Simplicity: Focus on required skills without unnecesary complexity.
- Flexibility: Design should be easy to extend (e.g., adding operations).
- Input Validation: Ensure the operations is one of the four allowed symbols.

## Program Structure

1. Main Components

  - Variables: Two floating-point numbers, an operation character, and a result variable.
  - Input Collection: Prompt and read two numbers and an operation.
  - Operation Logic: Use conditionals to process the chosen operation.
  - Output: Display the result clearly.

2. Flow of Execution

  - Show a welcome message.
  - Collect the first number.
  - Collect the second number.
  - Collect the operation.
  - Calculate and display the result.
  - (Optional) Ask if the user wants to repeat.
