/*
  Keyboard four pushbuttons
  Reads an array of pushbuttons. If any one has just been pressed,
  sends a keystroke from a corresponding array

  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 22 Feb 2020
  by Tom Igoe

*/

#include <Keyboard.h>
// debounce delay for pushbutton:
const int debounceDelay = 4;
int buttonCount = 4;
//  pushbuttons are on these pins:
int buttonPin[] = {2, 3, 4, 5};
// previous states of the buttons:
int lastButtonState[] = {HIGH, HIGH, HIGH, HIGH};
// characters to print when the buttons are pushed:
char buttonChar[] = {'l', 'r', 'u', 'd'};

void setup() {
  // initialize serial and Keyboard:
  Serial.begin(9600);
  Keyboard.begin();
  // set button input modes:
  for (int b = 0; b < buttonCount; b++) {
    pinMode(buttonPin[b], INPUT_PULLUP);
  }
}

void loop() {
  // iterate over the button list:
  for (int b = 0; b < buttonCount; b++) {
    // read this button:
    int buttonState = digitalRead(buttonPin[b]);
    // if it has changed:
    if (buttonState != lastButtonState[b]) {
      // wait until button state stabilizes:
      delay(debounceDelay);
      // if it's low:
      if (buttonState == LOW) {
        // send keystroke:
        Keyboard.print(buttonChar[b]);
        Serial.print(buttonChar[b]);
      }
      // save current state for next time:
      lastButtonState[b] = buttonState;
    }
  }
}
