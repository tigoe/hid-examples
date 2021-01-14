/*
  Mouse scroll wheel
  Moves the scroll wheel up and down continually.
  To see this in action, pick a window with a lot of content,
  one that requires scrolling.

  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 23 Feb 2020
  by Tom Igoe
*/

#include <Mouse.h>

int dir = 1;
void setup() {
  Mouse.begin();
}

void loop() {
  // scroll 10 times:
  for (int y = 0; y < 10; y++) {
    Mouse.move(0, 0, dir);
    delay(100);
  }
  // reverse the direction of scrolling:
  dir = -dir;
}
