/*
  Keyboard media player
  Reads an array of pushbuttons. If any one has just been pressed,
  sends a keystroke from a corresponding array

  Uses hid-project library instead of Keyboard.

  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 22 Feb 2020
  by Tom Igoe
*/

#include "HID-Project.h"

// debounce delay for pushbutton:
const int debounceDelay = 4;
int buttonCount = 4;
//  pushbuttons are on these pins:
int buttonPin[] = {2, 3, 4, 5};
// previous states of the buttons:
int lastButtonState[] = {HIGH, HIGH, HIGH, HIGH};

void setup() {
  // initialize serial and Consumer keys:
  Serial.begin(9600);
  Consumer.begin();
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
        // press the appropriate button:
        pressButton(b);
      }
      // save current state for next time:
      lastButtonState[b] = buttonState;
    }
  }
}

// sends a consumer key for each button:
void pressButton(int whichButton) {
  switch (whichButton) {
    case 0: 
      Consumer.write(MEDIA_PLAY_PAUSE);
      break;
    case 1:
      Consumer.write(MEDIA_NEXT);
      break;
    case 2:
      Consumer.write(MEDIA_PREV);
      break;
    case 3:
      Consumer.write(MEDIA_VOLUME_MUTE);
      break;
  }
}
