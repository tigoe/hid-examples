/*
  Adafruit joystick example

  Reads an Adafruit joystick and maps the X and Y outputs
  to a range from -1 to 1.  Also inverts the button reading
  so that pressed = 1 and unpressed = 0.

  circuit: Arduino Leonardo with Adafruit joystick attached to
  A0 through A4, with Vcc on A0
  (https://www.adafruit.com/products/512)

  Though written for the Leonardo, this will work on any of the
  USB-native models (MKR1xxx, Nano 33 IoT, Due, etc)

  created 10 Sept 2012
  modified 23 Feb 2020
  by Tom Igoe

*/

#include <Mouse.h>
int lastButton = HIGH;

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  // configure analog pins for Adafruit joystick:
  pinMode(A0, OUTPUT);
  pinMode(A4, OUTPUT);
  // joystick pushbutton:
  pinMode(A3, INPUT_PULLUP);
  // turn on A0 for +v connection of joystick:
  digitalWrite(A0, HIGH);
  // turn off A4 for gnd connection of joystick:
  digitalWrite(A4, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the inputs on analog pin 0 and 1:
  int x = analogRead(A1);
  delay(1);
  int y = analogRead(A2);
  // read the pushbutton:
  int button = !digitalRead(A3);

  // map x and y readings to a 3-point range
  // and subtract 1 to get -3 to 3, with
  // 0 at rest. You may have to modify the numbers
  // to make it work:
  x = map(x, 5, 1023, -4, 3) + 1;
  y = map(y, 5, 1023, -4, 3) + 1;

  // move the mouse:
  Mouse.move(x, y, 0);

  // if the button changes, press or release the mouse,
  // as appropriate.  LOW to HIGH = press, HIGH to LOW = release:
  if (button != lastButton) {
    if (button == HIGH) {
      Mouse.press(MOUSE_LEFT);
    }
    else {
      Mouse.release(MOUSE_LEFT);
    }
  }
  // print the results
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(button);
  // store the button state for comparison next time:
  lastButton = button;
}
