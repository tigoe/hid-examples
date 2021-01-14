/*
  Keyboard automator

  Creates a text file on a MacOS computer
  using the command line interface.
  There are several missing error checks, so
  beware of running this before checking it thoroughly.

  created 22 Feb. 2020
  by Tom Igoe
*/

#include <Keyboard.h>

void setup() {
  Keyboard.begin();
  // wait before starting the action:
  delay(4000);
}

void loop() {
  // press command-space to get search bar:
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(' ');
  Keyboard.releaseAll();
  delay(2000);
  // once you have search bar, search for terminal:
  Keyboard.print("terminal");
  // delay long enough to get list. Terminal app should
  // be first on it:
  delay(2000);
  // select first thing in search list:
  Keyboard.println();
  // wait for terminal app to open:
  delay(1000);
  // change directories to the desktop:
  Keyboard.println("cd ~/Desktop");
  delay(1000);
  // open a new file with the nano text editor:
  Keyboard.print("nano arduino_message.txt");
  // wait for user to read what you're about to do:
  delay(1000);
  // hit return:
  Keyboard.println();
  // wait for nano to open:
  delay(1000);
  // add some text in the editor:
  Keyboard.println("This is a message for you");
  Keyboard.println("from your Arduino.");
  Keyboard.println("How's it going?");
  // let the user catch up:
  delay(2000);
  // ctrl-x to save:
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('x');
  Keyboard.releaseAll();
  delay(1000);
  // y to confirm save:
  Keyboard.println('y');
  // wait for return to shell:
  delay(3000);
  // open the file you just created in the default viewer:
  Keyboard.print("open arduino_message.txt");
  // wait for user to see what you're doing:
  delay(1000);
  // hit the enter key:
  Keyboard.println();
  // wait for the file to open:
  delay(1000);

  // hold down the command key:
  Keyboard.press(KEY_LEFT_GUI);
  // increase the font size 15 times:
  for (int x = 0; x < 18; x++) {
    Keyboard.print('+');
    delay(300);
  }
  Keyboard.releaseAll();
  // stop the loop:
  while (true);
}
