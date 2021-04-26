# MENUINO UI

![Sample screen](https://github.com/gllortc/menuino/blob/master/docs/1618504383401.jpg)

## UI system for Arduino and touchscreens

This project is a simple way to create a complete UI system for TFT/LCD touchscreens for the Arduino microcontrollers (and other supported platforms). Actually the systems supports de following UI elements for the screens:

* *Text labels*: Text that can be changed by the code (for example, the temperature)
* *Push buttons*: Momentary pushbuttons
* *State buttons*: Buttons on/off
* *Menu buttons*
* *Progress bar*

## Creating screens

Each screen is a derived class of the `Screen` base class.

## Supported screens

**MENUINO** is platform independent, so you be able to use the display your project needs. Simply replace the libraries `MCUFRIEND_kbv` and `TouchScreen.h` and the initialization calls on the `TouchDisplay` class with the required by your display.

The current project is using an [OPEN-SMART TFT 3.2"](https://es.aliexpress.com/item/32755473754.html?spm=a219c.12010612.8148356.15.5a527fe3p5FXE7) connected to an [Arduino Mega](https://store.arduino.cc/arduino-mega-2560-rev3).

## Dependences

* EEPROM
* [EncoderMenuSwitch](https://github.com/gllortc/encodermenuswitch)
* [Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)
* MCUFRIEND_kbv (modified version for the OPEN-SMART TFT 3.2")
* [Adafruit TouchScreen](https://github.com/adafruit/Adafruit_TouchScreen)
* [XpressNet Client](http://pgahtow.de/wiki/index.php?title=XpressNet) (this library is used by the application, but you probably don't want it)
