/*
  Presses all the available keys in the Keyboard library
  
  Works on SAMD boards (MKR series, Nano 33 IoT),
  Leonardo, Due, and other USB-native boards

  created 22 Feb 2020
  by Tom Igoe
*/

#include <Keyboard.h>
int keyCount = 100;
byte keyList[] = {
  KEY_LEFT_CTRL,   // 0x80
  KEY_LEFT_SHIFT,  // 0x81
  KEY_LEFT_ALT,    // 0x82
  KEY_LEFT_GUI,    // 0x83
  KEY_RIGHT_CTRL,  // 0x84
  KEY_RIGHT_SHIFT, // 0x85
  KEY_RIGHT_ALT,   // 0x86
  KEY_RIGHT_GUI,   // 0x87

  KEY_UP_ARROW,    // 0xDA
  KEY_DOWN_ARROW,  // 0xD9
  KEY_LEFT_ARROW,  // 0xD8
  KEY_RIGHT_ARROW, // 0xD7
  KEY_BACKSPACE,   // 0xB2
  KEY_TAB ,        // 0xB3
  KEY_RETURN,      // 0xB0
  KEY_ESC ,        // 0xB1
  KEY_INSERT,      // 0xD1
  KEY_DELETE,      // 0xD4
  KEY_PAGE_UP ,    // 0xD3
  KEY_PAGE_DOWN,   // 0xD6
  KEY_HOME,        // 0xD2
  KEY_END ,        // 0xD5
  KEY_CAPS_LOCK,   // 0xC1
  KEY_F1,          // 0xC2
  KEY_F2,          // 0xC3
  KEY_F3,          // 0xC4
  KEY_F4,          // 0xC5
  KEY_F5,          // 0xC6
  KEY_F6,          // 0xC7
  KEY_F7,          // 0xC8
  KEY_F8,          // 0xC9
  KEY_F9,          // 0xCA
  KEY_F10,         // 0xCB
  KEY_F11,         // 0xCC
  KEY_F12,         // 0xCD
  KEY_F13,         // 0xF0
  KEY_F14,         // 0xF1
  KEY_F15,         // 0xF2
  KEY_F16,         // 0xF3
  KEY_F17,         // 0xF4
  KEY_F18,         // 0xF5
  KEY_F19,         // 0xF6
  KEY_F20,         // 0xF7
  KEY_F21,         // 0xF8
  KEY_F22,         // 0xF9
  KEY_F23,         // 0xFA
  KEY_F24          // 0xFB
};

String keyNames[] = {"KEY_LEFT_CTRL", "KEY_LEFT_SHIFT", "KEY_LEFT_ALT",
                     "KEY_LEFT_GUI", "KEY_RIGHT_CTRL", "KEY_RIGHT_SHIFT", "KEY_RIGHT_ALT",
                     "KEY_RIGHT_GUI", "KEY_UP_ARROW", "KEY_DOWN_ARROW", "KEY_LEFT_ARROW",
                     "KEY_RIGHT_ARROW", "KEY_BACKSPACE", "KEY_TAB", "KEY_RETURN", "KEY_ESC",
                     "KEY_INSERT", "KEY_DELETE", "KEY_PAGE_UP", "KEY_PAGE_DOWN", "KEY_HOME",
                     "KEY_END", "KEY_CAPS_LOCK", "KEY_F1", "KEY_F2", "KEY_F3", "KEY_F4",
                     "KEY_F5", "KEY_F6", "KEY_F7", "KEY_F8", "KEY_F9", "KEY_F10", "KEY_F11",
                     "KEY_F12", "KEY_F13", "KEY_F14", "KEY_F15", "KEY_F16", "KEY_F17",
                     "KEY_F18", "KEY_F19", "KEY_F20", "KEY_F21", "KEY_F22",
                     "KEY_F23", "KEY_F24"
                    };

void setup() {
  // initialize serial and Keyboard:
  Serial.begin(9600);
  Keyboard.begin();
  while (!Serial);
  delay(3000);
}

void loop() {
//press all the printable ASCII characters:
  for (int k = ' '; k < '~'; k++) {
    if (!Serial) return;
    Keyboard.press(k);
    Serial.write(k);
    Serial.print("  ");
    Serial.print(k);
    Serial.print("  ");
    Serial.print(k, HEX);
    Serial.println();
    delay(800);
    Keyboard.release(k);
  }

  // press all the keys in the special keys list from Keyboard.h:
  for (int k = 0; k < sizeof(keyList); k++) {
    byte thisKey = keyList[k];
    Keyboard.press(thisKey);
    Serial.print(keyNames[k]);
    Serial.print("  ");
    Serial.print(thisKey);
    Serial.print("  ");
    Serial.print(thisKey, HEX);
    Serial.print("  ");
    Serial.write(thisKey);
    Serial.println();
    delay(800);
    Keyboard.release(thisKey);
    // release the caps lock:
    if (thisKey == KEY_CAPS_LOCK) {
      Keyboard.press(thisKey);
      delay(10);
      Keyboard.release(thisKey);
    }
  }
  // stop:
  while (true);
}
