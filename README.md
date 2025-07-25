# gogo7-schematics
Schematic description of the GoGo Board 7 Hardware

<img src="images/ESP32-S3%20GoGo7%20Pinout.png" width="500">

## Table of Contents

- [Processor](#processor)
- [Bootloader](#bootloader)
- [Analog Input](#analog-input)
- [Joystick](#joystick)

---

## Processor

The GoGo Board uses the ESP32-S3 MCU by Espressif.  
It is the N16R8 variant with 16 MB of flash memory and 8 MB of RAM.  
This dual-core processor allows the GoGo Board firmware to efficiently handle background processes.  
The S3 also has a built-in USB module, used for communication with the host computer and for flashing the firmware.

---

## Bootloader

Because the GoGo Board does not use a USB-to-serial chip, firmware downloads are done over USB using the ESP32-S3's internal USB interface.  
The S3 comes with a pre-loaded USB CDC (virtual serial port) bootloader, which can be activated by holding the Boot button during power-up.

To flash new firmware, we recommend using the [Tasmota Web Installer](https://tasmota.github.io/install/).  
For detailed instructions, please see the [Firmware Update Procedure document](https://docs.google.com/document/d/1wkHplLRawxpCvvXY5K_7zhaUBPVLWB5iVyL8zbxunkI/edit?tab=t.0#heading=h.g8lrajqe9t70).

You can also write your own firmware using the Arduino IDE. The GoGo Board should be compatible with any generic ESP32-S3 board profile.  
**Remember:** Hold the Boot button at power-up to download your compiled code.

---

## Analog Input

<img src="images/analog_input.png" width="400">

The GoGo Board provides 4 analog inputs via white 4-pin Grove ports. Each port provides:
- Vcc (+5V)
- GND
- Signal

**Voltage Divider:**  
Since the ESP32-S3 uses 3.3V for its ADC inputs, a voltage divider circuit scales down the input signal from 5V to 3.3V.

Here are the pins used for the GoGo sensor ports:

| Sensor | Pin   |
|--------|-------|
| 1      | GPIO1 |
| 2      | GPIO2 |
| 3      | GPIO3 |
| 4      | GPIO5 |

---

## Joystick

The GoGo Board uses a 5-direction joystick (up, down, left, right, press) to control the built-in screen.  
A collection of resistors generates different voltages for each direction, all read on GPIO4.

<img src="images/joystick.png" width="400">

As shown in the schematic above, a 5.1K pull-up resistor keeps the GPIO high when nothing is pressed.  
The line is pulled to ground via the resistor associated with each direction pressed.  
The combination of pull-up and pull-down resistors forms a voltage divider, allowing each direction to generate a unique input voltage on the GPIO pin.
