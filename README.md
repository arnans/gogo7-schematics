# GoGo Board version 7 Schematics
Schematic description of the GoGo Board 7 Hardware

<img src="images/ESP32-S3%20GoGo7%20Pinout.png" width="500">

---

## Table of Contents

- [Processor](#processor)
- [Bootloader](#bootloader)
- [Joystick](#joystick)
- [Analog Input](#analog-input)
- [Built-in Sensors](#built-in-sensors)
  - [List of built-in sensors](#list-of-built-in-sensors)
  - [Accelerometer & Gyroscope](#accelerometer--gyroscope)
  - [Ambient Light Sensor](#ambient-light-sensor)
  - [Digital Microphone](#digital-microphone)
  - [Temperature & Humidity](#temperature--humidity)
  - [IR Receiver](#ir-receiver)
  - [IR Transmitter](#ir-transmitter)

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

## Joystick

The GoGo Board uses a 5-direction joystick (up, down, left, right, press) to control the built-in screen.  
A collection of resistors generates different voltages for each direction. The joystick is connected to GPIO4.

<img src="images/joystick.png" width="400">

A 5.1K pull-up resistor keeps the GPIO high when nothing is pressed.  
When the joystick is activated, each direction has a pull-down resistor with a unique value.  
The pull-up and pull-down combination forms a voltage divider, allowing each direction to generate a unique input voltage on the GPIO pin.

---

## Analog Input

<img src="images/analog_input.png" width="400">

The GoGo Board provides 4 analog inputs via white 4-pin Grove ports. Each port provides:
- Vcc (+5V)
- GND
- Signal

**Voltage Divider:**  
Since the ESP32-S3 uses 3.3V for its ADC inputs, a voltage divider circuit scales down the input signal from 5V to 3.3V. This circuit consists of two resistors: 11K and 22K ohms. This divider circuit also pulls down the AN GPIO when no sensor is connected, making the readout always zero.

Here are the pins used for the GoGo sensor ports:

| Sensor | Pin   |
|--------|-------|
| 1      | GPIO1 |
| 2      | GPIO2 |
| 3      | GPIO3 |
| 4      | GPIO5 |

---

## Built-in Sensors

The GoGo Board 7 has five built-in sensors, four of which are connected via an I2C bus. Only the Infrared receiver is connected to a GPIO.

### List of built-in sensors

| Sensor                    | Interface | Model            | Description                                                                                                       |
|---------------------------|-----------|------------------|-------------------------------------------------------------------------------------------------------------------|
| Accelerometer & Gyroscope | I2C       | LSM6DS3TR-C      | 3-axis accelerometer & gyroscope for motion detection and gesture sensing.                                        |
| Ambient Light Sensor      | I2C       | LTR-553ALS-01    | Provides ambient light and proximity readings with a built-in IR emitter.                                         |
| Digital Microphone        | I2S       | SD18OB261-060    | Digital MEMS omnidirectional microphone with I²S output for loudness sensing.                                     |
| Temperature & Humidity    | I2C       | GXHT30C          | Digital temperature & humidity sensor (±0.3°C, ±3% RH accuracy).                                                  |
| IR transmitter & receiver | GPIO      | C414640          | 38 kHz IR remote receiver and directional IR LED transmitter driven by a transistor.                              |

---

### Accelerometer & Gyroscope

<img width="763" height="478" alt="image" src="https://github.com/user-attachments/assets/77a7954a-449b-4b19-9a70-7cc0a5d07fdf" />

- Uses the 1st I2C on the ESP32 (SDA=GPIO8, SCL=GPIO9)
- The interrupt output is connected to INT-ACC (GPIO47) on the ESP32 (not currently used by firmware).

---

### Ambient Light Sensor

<img width="552" height="384" alt="image" src="https://github.com/user-attachments/assets/e9da9e0b-63fe-4960-9178-215e2cbc3c5a" />

- Uses the 1st I2C on the ESP32 (SDA=GPIO8, SCL=GPIO9)
- Outputs brightness in Lux. Note: the GoGo's screen may interfere with readings, especially in low light.
- The interrupt output pin is **not** connected to the ESP32.

---

### Digital Microphone

<img width="679" height="337" alt="image" src="https://github.com/user-attachments/assets/7fdcc020-47a0-42eb-b797-dc5e47476888" />

- Digital MEMS microphone with I²S output, suitable for measuring loudness.

---

### Temperature & Humidity

<img width="730" height="381" alt="image" src="https://github.com/user-attachments/assets/300c08ad-b265-48a2-8ad9-702d2d88bf3a" />

- Uses the 1st I2C on the ESP32 (SDA=GPIO8, SCL=GPIO9)
- SHT30-compatible module for temperature and humidity.

---

### IR Receiver

<img width="633" height="286" alt="image" src="https://github.com/user-attachments/assets/1d122b78-355a-4c78-9bf2-2f882731c3d1" />

- Connected via a GPIO to the ESP32.
- Firmware currently decodes SONY-compatible IR remote signals; can support any 38 kHz protocol.

---

### IR Transmitter

<img width="848" height="369" alt="image" src="https://github.com/user-attachments/assets/fba83c2d-6a8e-40df-afee-5994e43496e9" />

- IR LED with a narrow 15-degree beam angle for directional transmission.
