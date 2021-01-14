/*
  Keyboard pushbutton
  Reads a pushbutton and if it's just been pressed,
  sends a Z as a keystroke

  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 22 Feb 2020
  by Tom Igoe

*/

#include <Keyboard.h>
// pushbutton on pin 2 is connected to ground:
const int buttonPin = 2;
// debounce delay for pushbutton:
const int debounceDelay = 4;
// previous state of the button:
int lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  // set button input mode:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read button:
  int buttonState = digitalRead(buttonPin);
  // if it has changed:
  if (buttonState != lastButtonState) {
    // wait until button state stabilizes:
    delay(debounceDelay);
    // if it's low:
    if (buttonState == LOW) {
      // send keystroke:
      Keyboard.print('Z');
      Serial.print('Z');
    }
    // save current state for next time:
    lastButtonState = buttonState;
  }
}
