#include "buttons.h"

// Define an array to store the state of each button (pressed or not pressed)
volatile bool buttonState[] = {HIGH, HIGH, HIGH, HIGH, HIGH};  // Initial state is HIGH (not pressed)

// Define an array to store the start time of each button press
volatile unsigned long buttonStartTime[] = {0, 0, 0, 0, 0};  // Initial time is 0

// Set the debounce time for button presses
const unsigned long debounceTime = 3;  // Adjust debounce time as needed

// Function to initialize buttons and button interrupts
void initButtonsAndButtonInterrupts(void)
{
  // Set the mode for each button pin as INPUT_PULLUP
  pinMode(firstPin, INPUT_PULLUP);
  pinMode(secondPin, INPUT_PULLUP);
  pinMode(thirdPin, INPUT_PULLUP);
  pinMode(lastPin, INPUT_PULLUP);
  pinMode(gameStartPin, INPUT_PULLUP);

  /* Enable Pin Change Interrupts on D-bus; This is the Pin Change Interrupt Control Register.
  It controls the overall operation of Pin Change Interrupts for the microcontroller. */
  PCICR |= (1 << PCIE2); // Enable PCINT23:8 interrupts

  // Enable interrupts for each button pin
  PCMSK2 |= (1 << PCINT18); // Pin 2
  PCMSK2 |= (1 << PCINT19); // Pin 3
  PCMSK2 |= (1 << PCINT20); // Pin 4
  PCMSK2 |= (1 << PCINT21); // Pin 5
  PCMSK2 |= (1 << PCINT22); // Pin 6

  // Enable global interrupts
  sei();  
}
