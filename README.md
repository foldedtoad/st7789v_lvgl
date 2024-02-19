# Zephyr Support for ST7789 Display

## Overview
Display "Hello World" and a dynamic counter using LVGL.  

This sample application displays some simple LvGL capabilities using a Pico-W and ST7789V display panel.

It is hoped this project will provide a template for for ST7789 support on other SoC+board combinations.

See the following video links --
* [Pico-W rp2040](https://youtu.be/FVRU7HFSb6Y)  fix me!

## Requirements

Display panel and a board which provides a configuration
for example:

* **ST7789V** based display panel:  [example](https://www.aliexpress.us/item/3256805850192151.html).
* **PICO or PICO-W** Raspberry Pi RP2040 Eval Board.
* **Momentary Switches** (4 each)

### Wiring and Soldering
The 0.10" headers will need to be soldered onto the display pannel. In addition, wiring between the display panel and the PCA10056 board needs to be made.  
Review the ***overlay*** files for wire-to-pin specifics.

Be sure to wire the backlight pin, othewise the panel will remain dark.

## How to Build
This project was developed using Zephyr V3.5, and successfully built on both Ubuntu and MacOS.  

**NOTE** -- building may take longer that expected as LVGL has quite a bit of code.

**NOTE** -- The default resolution settings in the ***overlay*** files are set to 320x170.  
Many displays will have a resolution of 320x240, so update the height and width parameters according to your display panel's resolution.

### CMake Method
This build method use cmake directly, and doesn't use west or ninja.  
Edit the CMakeList.txt file to select the target board.
1) ***cd*** to st7789v_alternate directory
2) ***./configure.sh***
3) ***cd build***
4) ***make -j6***

### West Method
1) ***cd*** to st7789v_alternate directory
2) ***rm -rf build***
3) ***west build -b rpi_pico_w**
