/*
  HID Enable/Disable with a pushbutton

  This sketch shows how to use a pushbutton on a hardware
  interrupt pin to enable or disable Mouse and Keyboard control.

  When control is enabled, it does annoying but non-destructive
  actions with the mouse and keyboard. When disabled, you
  have control with your real mouse and keyboard.

  circuit:
  - pushbutton on pin 2, attached to ground.
  
  created 23 Feb 2020
  by Tom Igoe

*/

#include <Keyboard.h>
#include <Mouse.h>

// the enable button should be on a hardware interrupt
// pin. Check your board's reference to find them:
const int HIDEnableButton = 2;
// delay for button debounce, in ms:
int debounceDelay = 4;
// whether or not HID is enabled:
volatile bool HIDEnabled = false;

// x and y movements for the mouse:
int x = 1;
int y = 1;

void setup() {
  // set up the pinMode and interrupt service routine:
  pinMode(HIDEnableButton, INPUT_PULLUP);
  attachInterrupt(HIDEnableButton, HIDChange, FALLING);
}

void loop() {
  if (HIDEnabled) {
    // do all your keyboard and mouse things inside
    // this conditional statement. For example:

    // move the mouse 100 pixels:
    for (int m = 0; m < 100; m++) {
      Mouse.move(x, y, 0);
    }
    // reverse direction of x and y for next time:
    x = -x;
    y = -y;

    // move the text cursor left, then right:
    Keyboard.write(KEY_LEFT_ARROW);
    delay(500);
    Keyboard.write(KEY_RIGHT_ARROW);
    delay(500);
  }
}

// interrupt handler for the HID Enable button:
void HIDChange() {
  // debounce:
  delay(debounceDelay);
  // if the button is still low, change the state
  // of the HID control:
  if (digitalRead(HIDEnableButton) == LOW) {
    HIDEnabled = !HIDEnabled;
  }
  if (HIDEnabled) {
    Mouse.begin();
    Keyboard.begin();

  } else {
    Mouse.end();
    Keyboard.end();
  }
}
