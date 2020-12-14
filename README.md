# ESP32 Graphing Calculator

A simple graphing calculator powered by the ESP32 SoC from Espressif.

Software built with the Arduino IDE and Espressif's [ESP32 Arduino Core](https://github.com/espressif/arduino-esp32).

Created solely for educational purposes. 

_Fun fact: roughly 3x faster than the Texas Instruments TI-84 Plus!_

## Hardware
* Generic ESP32 dev module (any dev module should work)
* 1.77" 128x160 TFT LCD - ST7735S controller

## Libraries
* [Adafruit ST77xx library](https://github.com/adafruit/Adafruit-ST7735-Library)
* [Adafruit GFX graphics libray](https://github.com/adafruit/Adafruit-GFX-Library)

## Wiring diagram
Coming soon!

## Feature list
* Renders graphs of functions on the display


## Photos

Functions shown below:
* Sine wave: y = 6 sin(x)
* Parabola: y = (0.6 x)<sup>3</sup> - 5 x
* Cubic funcion: y = (0.6 x)<sup>3</sup> - 5 x

Viewing window:
```
xmin = -10;
xmax = 10;
xscl = 1;

ymin = -10;
ymax = 10;
yscl = 1;

xres = (xmax - xmin)/tft.width();
yres = (ymax - ymin)/tft.height();
```

![ESP32](https://i.imgur.com/NnfdsFd.jpg)
