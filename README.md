# HID Examples

These examples show how to create Human Interface Devices (HID) with Arduinos. Examples use the  [Keyboard](https://www.arduino.cc/reference/en/language/functions/usb/keyboard/) and [Mouse](https://www.arduino.cc/reference/en/language/functions/usb/mouse/) libraries to emulate a USB keyboard or mouse. There are also some examples that use the [HID-project](https://github.com/NicoHood/HID/wiki) library, which extends Keyboard and Mouse to do things like using the consumer keys (alternate functions of the F-keys), power key, and so forth. 

These should all work on the USB-native boards, including the SAMD Arduino boards (MKR series, Nano 33 IoT), Leonardo, Micro, and Due. 

## Note on Mouse, Keyboard, and Serial Ports

All Arduinos appear to your personal computer's operating system as an asynchronous serial port, sometimes called a **COM port** or Universal **Asyncronous Receiver-Trasmitter (UART)**. This is its USB profile, and when you plug it into your computer, the operating system notes that profile and adds it to the list of USB devices. 
When you program an Arduino to behave as an HID device, you're giving it an additional USB profile. 

When you include the Keyboard library in a sketch, your board's serial port number will change. For example, on MacOS, if the port number is `/dev/cu.usbmodem14101`, then adding the Keyboard library will change it to `/dev/cu.usbmodem14102`. Versions of the Arduino IDE from 1.8.13 and higher will automatically adjust the serial port selected when you do this, but earlier versions won't, and other applications using the serial port won't, so you might need to make the adjustment yourself. 

Removing the Keyboard library will change it back to its previous enumeration Similarly, if you double-tap the reset button to put the board in bootloader mode, the serial port will re-enumerate to its original number.

## Note for Windows Users

Windows won't automatically recognize your Arduino as a new composite device (e.g. a Mouse and a COM port) when you use these libraries. You need to make some driver changes. [This page explains it](https://github.com/arduino/ArduinoCore-samd/releases/tag/1.8.2) pretty well. In summary, you need to:

* Upload your first Mouse or Keyboard sketch
* Open the Windows System Control panel Device manager 
* Under COM ports, choose your device, which should be marked with a yellow exclamation point indicating Windows can't find the drivers. 
* In the resulting window, click the Driver tab and select "Update Driver"
* Select "Browse My Computer for Driver Software"
* Select "Let me pick from a list of available drivers on my computer"
* Select "USB Input device"

You will have to do this each time you upload new code, so it's wise to work out your sketch using serial output, then switch to USB when you know the logic of the sketch works. 

## Recovering From a Runaway HID Sketch

Programs which control your keyboard and mouse can make development difficult or impossible if you make a mistake in your code. If you create a mouse or keyboard example that doesn't do what you want it to, and you need to reprogram your microcontroller to stop the program, do this:

### Open a new blank sketch.

This sketch is your recovery:
````
void setup() {

}
void loop() {

}
````

Programming the board with this blank sketch removes your mistaken sketch and gives you control again.  To do this, however, you need the current sketch to stop running. So:

### Put the microcontroller in bootloader mode and upload the blank sketch

On the SAMD boards, you can do this by double-tapping the reset button. The on-board LED will begin glowing, and the bootloader will start so that you get a serial port enumeration, but the sketch won't run.  On the Leonardo and other 32U4-based boards, hold the reset down until you've given the upload command. The 32U4 bootloader will take a few seconds before it starts the sketch, so the uploader can take command and load your blank sketch. 

Once you've got the blank sketch on the board, review the logic of your mistaken Keyboard or Mouse sketch and find the problem before uploading again.

## Add an HID Enable Button

You don't have to control the mouse or keyboard all the time in your sketch. If you add a pushbutton whose function is to enable or disable Mouse and Keyboard, you can experiment with all kinds of things in your sketch and still have a way to disengage keyboard and mouse control. It's not a bad idea to put this button on an interrupt pin so that the button will do its job no matter what.  The [HIDEnable](https://github.com/tigoe/ArduinoGeneralExamples/tree/master/KeyboardMouseExamples/HIDEnable) sketch shows one way to implement this.