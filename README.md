# gogo7-schematics
Schematic description of the GoGo Board 7 Hardware

<img src="images/ESP32-S3%20GoGo7%20Pinout.png" width="500">

# Contents

- [The Processor](#Processor)





# Processor

The GoGo Board uses the ESP32-S3 mcu by Espressive. It is a varient with 16 MB of flash memory and 8 MB of RAM (N16R8). This is a dual-core processor that allows the GoGo Board firmware to efficiently make use of background processes. The S3 also has a built-in USB module which is used for communication with the host computer and for flashing the firmware. 

# Bootloader

The GoGo Board uses a USB CDC bootloader, which can be activated by holding the Boot button during power-up. To flash a new firmware, we suggest using the [Tasmota Web Installer](https://tasmota.github.io/install/). Read the [Firmware Update Procedure document](https://docs.google.com/document/d/1wkHplLRawxpCvvXY5K_7zhaUBPVLWB5iVyL8zbxunkI/edit?tab=t.0#heading=h.g8lrajqe9t70)  for more information about how to flash the GoGo Board.

You can also write your own firmware using the Arduino IDE. The GoGo Board should be compatible with any generic ESP32-S3 board profile. Hold the boot button at power-up.  





