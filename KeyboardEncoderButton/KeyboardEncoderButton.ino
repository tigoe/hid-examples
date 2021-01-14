/*
  A crude encoder-and-button keyboard
  Allows for text entry using one hand, with encoder and pushbutton.
  Turning the encoder to the right advances the characters through the
  ASCII table. Turning it to the left decreases the character value.
  Pressing the button selects the character and advances the cursor.
  At the low end of the characters, space is followed by tab,
  then DELETE. At the upper end of the characters,
  ~ is followed by carriage return and newline.

  Circuit:
    - rotary encoder attached to pins 4 and 5
    - pushbutton attached to pin 3, connected to ground

  created 23 Feb 2019
  modified 23 Feb 2020
  by Tom Igoe
*/

#include <Keyboard.h>
#include <Encoder.h>

const int buttonPin = 3;    // pushbutton pin
Encoder knob(4, 5);         // encoder on pins 4 and 5
int lastButtonState = LOW;  // last button state
int lastKnobState = -1;     // last knob state
int timestamp = 0;          // timestamp
int rollover = 2000;        // pushbutton rollover
char character = 'a';       // currently displayed character

void setup() {
  // initialize button pin and Serial and keyboard:
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  // read the sensors:
  int buttonState = digitalRead(buttonPin);
  int knobState = knob.read();

  // if the button has changed:
  if (buttonState != lastButtonState) {
    // debounce the button:
    delay(4);
    // if button is pressed:
    if (buttonState == LOW) {
      // write the current character and take a timestamp:
      Keyboard.write(character);
      timestamp = millis();
    }
    // save current state for next time through the loop:
    lastButtonState = buttonState;
  }
  // if the button remains pressed, rollover:
  if (buttonState == LOW) {
    // after the rollover delay passes:
    if (millis() - timestamp > rollover) {
      // write the current character again:
      Keyboard.write(character);
      // delay 1/10 of the initial rollover time:
      delay(rollover / 10);
    }
  }

  // compare current and last knob state:
  int knobChange = knobState - lastKnobState;
  // if it's changed by 4 or more (one click):
  if (abs(knobChange) >= 4) {
    // get the direction (-1 or 1):
    int knobDirection = (knobChange / abs(knobChange));
    //add it to the current character:
    character += knobDirection;

    // there are several edge cases:
    switch (character) {
      case 0X1F:        // unprintables below space in ASCII table
        // replace with tab instead:
        character = '\t';
        Keyboard.write(character);
        break;
      case '\t':        // tab:
        // since last character was tab, replace with delete:
        Keyboard.write(KEY_DELETE);
        // reset current character:
        character = 'a';
        break;
      case 127:         // DEL
        // print newline and carriage return instead:
        Keyboard.println();
        break;
      default:
        // delete, then print character, then advance
        Keyboard.write(8);
        Keyboard.write(character);
        break;
    }
    // constrain character to between tab and ~:
    character =  constrain(character, '\t', '~');
    // save knobState for next time through loop:
    lastKnobState = knobState;
  }
}
