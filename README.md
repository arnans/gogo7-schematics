# gogo7-schematics
Schematic description of the GoGo Board 7 Hardware

<img src="images/ESP32-S3%20GoGo7%20Pinout.png" width="500">

# Contents

- [The Processor](#Processor)





# Processor

The GoGo Board uses the ESP32-S3 mcu by Espressive. It is a varient with 16 MB of flash memory and 8 MB of RAM (N16R8). This is a dual-core processor that allows the GoGo Board firmware to efficiently make use of background processes. The S3 also has a built-in USB module which is used for communication with the host computer and for flashing the firmware. 

# Bootloader

Because the GoGo Board does not use a USB to serial chip, firmware downloads are done over USB using the ESP32-S3's internal USB interface. The S3 comes with a pre-loaded USB CDC (Virtual serial port) bootloader, which can be activated by holding the Boot button during power-up. To flash a new firmware, we suggest using the [Tasmota Web Installer](https://tasmota.github.io/install/). Fo detailed procedure, please read the [Firmware Update Procedure document](https://docs.google.com/document/d/1wkHplLRawxpCvvXY5K_7zhaUBPVLWB5iVyL8zbxunkI/edit?tab=t.0#heading=h.g8lrajqe9t70). 

You can also write your own firmware using the Arduino IDE. The GoGo Board should be compatible with any generic ESP32-S3 board profile. Hold the boot button at power-up to download your compiled code.  

# Analog Input

<img src="images/analog_input.png" width="400">

The GoGo Board provides 4 analog inputs via white 4-pin grove ports. Each port provides the following:
- Vcc (+5V)
- GND
- Signal

**Voltage Divider**. Since the ESP32-S3 uses 3.3V for its ADC inputs, there is a voltage divider circuit that scales down the input signal from 5 to 3.3V.  

Here are the pins used for the GoGo's sensor port
| Sensor | Pin   |
|--------|-------|
| 1      | GPIO1 |
| 2      | GPIO2 |
| 3      | GPIO3 |
| 4      | GPIO5 |

# Joystick

The GoGo uses a 5-direction joystick (up, down, left, right, press) to control the built-in screen. A collection of resistors are used to generate different voltages for each direction. This voltage is fed into GPIO4. 

<img src="images/joystick.png" width="400">

As shown in the schematic above, A 5.1K pull-up resistor is used to keep the GPIO high when nothing is pressed. This line is then pulled to ground via the resistor accociated with each direction being pressed. The combination of pullup and pulldown resistors forms a voltage divider, allowing each direction to generate different input voltages on the GPIO pin. 
 

