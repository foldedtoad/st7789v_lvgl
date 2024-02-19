# Zephyr Support for ST7789 Display

## Overview
Display "Hello World" and a dynamic counter using LVGL.  

This sample application displays "Hello World" in the center of the screen
and a counter at the bottom which increments every second. 

It is hoped this project will provide a template for for ST7789 support on other SoC+board combinations.

See the following video links --
* [PCA10056 nRF52840](https://studio.youtube.com/video/sml6Ic_K4g4) 
* [Pico-W rp2040](https://youtu.be/FVRU7HFSb6Y)

## Requirements

Display shield and a board which provides a configuration
for example:

* [**ST7789**](https://www.aliexpress.us/item/3256805850192151.html) display panel.
* **PCA10056** Nordic nRF52840 Eval Board.
* **PICO or PICO-W** Raspberry Pi RP2040 Eval Board.

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
3) ***west build -b board-name***  -- board-name is either **nrf52840dk_nrf52840** or **rpi_pico_w**
