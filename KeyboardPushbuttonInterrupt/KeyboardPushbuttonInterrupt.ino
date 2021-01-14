/*
  Keyboard pushbutton using hardware interrupt
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
// whether button has changed or not:
volatile bool buttonChanged = false;

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  // set button input mode:
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(buttonPin, buttonEvent, CHANGE);
}

void loop() {
  // if the button change flag is true, take action:
  if (buttonChanged) {
    // send keystroke:
    Keyboard.print('Z');
    Serial.print('Z');
    // clear button change flag:
    buttonChanged = false;
  }
}


void buttonEvent() {
  // wait for debounce:
  delay(debounceDelay);
  // if button is pressed, set button change flag:
  if (digitalRead(buttonPin) == LOW) {
    buttonChanged = true;
  }
}
