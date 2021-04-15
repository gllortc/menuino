# MENUINO UI
## UI system for Arduino and touchscreens

This project is a simple way to create a complete UI system for TDT/LCD touchscreens for the Arduino microcontrollers (and other supported platforms).

## Creating screens

Each screen is an extended class of the `Screen` class.

## Supported screens

**MENUINO** is platform independent, so you be able to use the display your project needs. Simply replace the library `MCUFRIEND_kbv` and the initialization calls on the `TouchDisplay` class with the required by your display.

The current project is using an [OPEN-SMART TFT 3.2"](https://es.aliexpress.com/item/32755473754.html?spm=a219c.12010612.8148356.15.5a527fe3p5FXE7) connected to an Arduino Mega.
