/*
  Apple keyboard init

  When you first plug in a USB keyboard to a MacOS computer,
  the Keyboard identifier helper pops up, and expects you to
  press the key to the right of your left shift key to identify
  the keyboard. This sketch does that, then prints some text

  created 22 Feb 2020
  by Tom Igoe
*/

#include <Keyboard.h>

void setup() {
  Keyboard.begin();
  Keyboard.press('Z');
  delay(10000);
  Keyboard.release('Z');
}

void loop() {
  delay(500);
  Keyboard.println("Hi there");
  // stop the loop:
  while (true);
}
