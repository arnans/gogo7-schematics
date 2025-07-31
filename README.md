# GoGo Board Version 7 Schematics

Schematic description of the GoGo Board 7 hardware.

<img src="images/ESP32-S3%20GoGo7%20Pinout.png" width="500">

---

## Table of Contents

- [1. Processor](#1-processor)
- [2. Bootloader](#2-bootloader)
- [3. Joystick](#3-joystick)
- [4. Analog Input](#4-analog-input)
- [5. Built-in Sensors](#5-built-in-sensors)
  - [5.1 List of Built-in Sensors](#51-list-of-built-in-sensors)
  - [5.2 Accelerometer & Gyroscope](#52-accelerometer--gyroscope)
  - [5.3 Ambient Light Sensor](#53-ambient-light-sensor)
  - [5.4 Digital Microphone](#54-digital-microphone)
  - [5.5 Temperature & Humidity](#55-temperature--humidity)
  - [5.6 IR Receiver](#56-ir-receiver)
  - [5.7 IR Transmitter](#57-ir-transmitter)
- [6. DC Motor Port](#6-dc-motor-port)
  - [6.1 The DRV8837 Driver Circuit](#61-the-drv8837-driver-circuit)
  - [6.2 The TLC59116IRHBR I2C PWM Driver](#62-the-tlc59116irhbr-i2c-pwm-driver)
  - [6.3 Chain Port (DC Motor Extension)](#63-chain-port-dc-motor-extension)
- [7. Servo / Relay Port](#7-servo--relay-port)
- [8. Expansion Ports](#8-expansion-ports)
  - [8.1 I2C Expansion Port](#81-i2c-expansion-port)
  - [8.2 UART Expansion Port](#82-uart-expansion-port)
  - [8.3 I/O Expansion Port](#83-io-expansion-port)
- [9. Tasmota Core](#9-tasmota-core)
  - [9.1 GPIO Ports](#91-gpio-ports)
  - [9.2 I2C Port](#92-i2c-port)
- [10. RGB LEDs](#10-rgb-leds)
- [11. 1.8 Inch LCD Display](#11-18-inch-lcd-display)

---

<img width="843" height="527" alt="image" src="https://github.com/user-attachments/assets/fc982578-030b-44f5-9e06-8051a504bcbb" />
<img width="795" height="558" alt="image" src="https://github.com/user-attachments/assets/4a9b0fb2-7955-47f6-9b6a-35d91d4d2aec" />



## 1. Processor

<img width="909" height="561" alt="image" src="https://github.com/user-attachments/assets/fed31f8d-e783-48cf-9a7e-258974682acd" />

The GoGo Board uses the ESP32-S3 MCU by Espressif (N16R8 variant: 16 MB flash, 8 MB RAM).  
This dual-core processor enables the firmware to efficiently handle background tasks.  
A built-in USB module is used for host communication and firmware flashing.

---

## 2. Bootloader

The GoGo Board does not use a USB-to-serial chip.  
Firmware updates are performed over USB using the ESP32-S3's internal USB CDC (virtual serial port) bootloader, which is activated by holding the Boot button during power-up.

To flash new firmware, use the [Tasmota Web Installer](https://tasmota.github.io/install/).  
Detailed steps can be found in the [Firmware Update Procedure](https://docs.google.com/document/d/1wkHplLRawxpCvvXY5K_7zhaUBPVLWB5iVyL8zbxunkI/edit?tab=t.0#heading=h.g8lrajqe9t70).

You can also program the board using the Arduino IDE (use a generic ESP32-S3 profile).  
**Note:** Hold the Boot button at power-up to enter download mode.

---

## 3. Joystick

The GoGo Board features a 5-direction joystick (up, down, left, right, press) connected to GPIO4.  
Different resistor values generate unique voltages for each direction, read by the ADC.

<img src="images/joystick.png" width="400">

A 5.1 kΩ pull-up resistor keeps GPIO4 high when inactive.  
Each direction uses a distinct pull-down resistor, forming a voltage divider that produces a unique ADC value per direction.

---

## 4. Analog Input

<img src="images/analog_input.png" width="400">

The board provides four analog inputs via white 4-pin Grove ports:
- Vcc (+5 V)
- GND
- Signal

**Voltage Divider:**  
Since the ESP32-S3 ADC uses 3.3 V max, each input uses a voltage divider (11 kΩ/22 kΩ) to scale 5 V signals to safe levels.  
When no sensor is connected, the divider pulls the analog GPIO low, resulting in a reading of zero.

| Sensor | Pin   |
|--------|-------|
| 1      | GPIO1 |
| 2      | GPIO2 |
| 3      | GPIO3 |
| 4      | GPIO5 |

---

## 5. Built-in Sensors

The GoGo Board 7 includes five built-in sensors: four on I2C, one on GPIO.

### 5.1 List of Built-in Sensors

| Sensor                    | Interface | Model            | Description                                                                                 |
|---------------------------|-----------|------------------|---------------------------------------------------------------------------------------------|
| Accelerometer & Gyroscope | I2C       | LSM6DS3TR-C      | 3-axis accelerometer and gyroscope for motion/gesture detection.                            |
| Ambient Light Sensor      | I2C       | LTR-553ALS-01    | Ambient light/proximity sensor with built-in IR emitter.                                    |
| Digital Microphone        | I2S       | SD18OB261-060    | Digital MEMS omnidirectional microphone with I²S output (loudness sensing).                 |
| Temperature & Humidity    | I2C       | GXHT30C          | Digital temperature/humidity sensor (±0.3°C, ±3% RH accuracy).                              |
| IR transmitter & receiver | GPIO      | C414640          | 38 kHz IR remote receiver and directional IR LED transmitter, transistor-driven.            |

---

### 5.2 Accelerometer & Gyroscope

<img width="534" height="335" alt="image" src="https://github.com/user-attachments/assets/77a7954a-449b-4b19-9a70-7cc0a5d07fdf" />

- Uses ESP32 I2C (SDA=GPIO8, SCL=GPIO9).
- Interrupt output is connected to INT-ACC (GPIO47) but is unused by current firmware.

---

### 5.3 Ambient Light Sensor

<img width="386" height="269" alt="image" src="https://github.com/user-attachments/assets/e9da9e0b-63fe-4960-9178-215e2cbc3c5a" />

- I2C bus (SDA=GPIO8, SCL=GPIO9).
- Reports brightness in lux.
- The GoGo’s screen may affect readings in low light.
- Interrupt output is **not** connected (no available GPIO).

---

### 5.4 Digital Microphone

<img width="475" height="236" alt="image" src="https://github.com/user-attachments/assets/7fdcc020-47a0-42eb-b797-dc5e47476888" />

- Digital MEMS mic with I²S output.
- Enables sound/loudness detection.

---

### 5.5 Temperature & Humidity

<img width="511" height="267" alt="image" src="https://github.com/user-attachments/assets/300c08ad-b265-48a2-8ad9-702d2d88bf3a" />

- I2C bus (SDA=GPIO8, SCL=GPIO9).
- SHT30-compatible sensor.

---

### 5.6 IR Receiver

<img width="443" height="200" alt="image" src="https://github.com/user-attachments/assets/1d122b78-355a-4c78-9bf2-2f882731c3d1" />

- Connected via GPIO to ESP32.
- Decodes SONY-compatible IR signals (can support any 38 kHz protocol).

---

### 5.7 IR Transmitter

<img width="594" height="258" alt="image" src="https://github.com/user-attachments/assets/fba83c2d-6a8e-40df-afee-5994e43496e9" />

- IR LED with a narrow (15°) beam for directional transmission.

---

## 6. DC Motor Port

The board provides four DC motor ports, each with a dedicated DRV8837 H-bridge driver (1.8 A peak, 5 V).  
**Lab tests:** Do not exceed 1 A per channel to avoid overheating.  
Each driver has built-in overcurrent and thermal protection.  
Note: Standard USB power sources are insufficient for all ports at full load.

Motor drivers are controlled by an I2C PWM chip (TLC59116IRHBR) due to limited ESP32 GPIOs.

### 6.1 The DRV8837 Driver Circuit

<img width="561" height="265" alt="image" src="https://github.com/user-attachments/assets/2afb4a5d-ceb5-4a2b-bbf6-b54aaeae0308" />

**Drive pins:** Each port requires three pins:
- **Enable:** Activates the driver.
- **IN1, IN2:** Control output state and polarity (see datasheet for logic).

**Pull-up resistors:**  
DRV8837 features weak internal pull-downs (~100 kΩ, see datasheet 7.3.3).  
As the I2C PWM driver is open-drain (logic low only), external 5.1 kΩ pull-ups are used to ensure a strong logic high.

### 6.2 The TLC59116IRHBR I2C PWM Driver

<img width="680" height="302" alt="image" src="https://github.com/user-attachments/assets/11f2270a-5c78-4bba-b849-c971ad54590b" />

- I2C addressable PWM (SDA=GPIO8, SCL=GPIO9).
- 16 channels: 12 drive the 4 H-bridge chips, 2 handle ESP32-C3 boot/RESET, 2 unused.
- RESET is wired to ESP32-S3 (M_RESET), allowing reboot of the PWM chip (not used in standard firmware due to high chip reliability).

### 6.3 Chain Port (DC Motor Extension)

<img width="342" height="185" alt="image" src="https://github.com/user-attachments/assets/8ff11924-d15f-4c7f-b99c-f2837b3239ab" />

A 4-pin Grove port (top right) exposes the ESP32-S3's I2C bus for additional DC motor ports using extension boards.  
The PWM chip supports up to 16 unique I2C addresses, allowing expansion up to 64 motor outputs.

<img width="398" height="268" alt="image" src="https://github.com/user-attachments/assets/a462dffc-d5e1-46d3-a511-2e6897526bc9" />

*Example: Motor extension module.*

---

## 7. Servo / Relay Port

<img width="311" height="482" alt="image" src="https://github.com/user-attachments/assets/d5e8f470-b9ce-4765-90d6-20180f57b8fa" />

Four Grove ports multiplex servo and relay control.  
These outputs supply 5 V, with current limiting and noise suppression to minimize voltage spikes under load.

<img width="403" height="151" alt="image" src="https://github.com/user-attachments/assets/ffa96320-cac1-4945-a8e1-c4db2b152796" />

---

## 8. Expansion Ports

### 8.1 I2C Expansion Port

<img width="393" height="193" alt="image" src="https://github.com/user-attachments/assets/3180b292-49f2-43af-8788-13d0853a099f" />

- Black Grove port.
- Connects to the ESP32-S3's secondary I2C bus (SCL2, SDA2).
- 5.1 kΩ pull-ups on both lines.
- 3.3 V logic.

### 8.2 UART Expansion Port

<img width="366" height="163" alt="image" src="https://github.com/user-attachments/assets/40f2b42f-d1d8-4d75-8046-e5f6debfe717" />

- Blue Grove port.
- Connects to ESP32-S3 UART0.
- 3.3 V logic.

### 8.3 I/O Expansion Port

<img width="652" height="212" alt="image" src="https://github.com/user-attachments/assets/79f24ff3-e62b-472f-9213-88de0d125cde" />

- Female pin header on the bottom side.
- Exposes various I/O and power pins for add-on board development.

---

## 9. Tasmota Core

<img width="849" height="524" alt="image" src="https://github.com/user-attachments/assets/f404164e-f9f0-4ccd-845c-c2cbfdd6e18f" />

The GoGo Board uses a second MCU as a co-processor: the ESP32-C3.  
There is a dedicated 3.3 V power regulator for the C3 and its peripherals.  
A second USB-C port connects to the ESP32-C3's USB interface for firmware downloads.  
The C3 comes preloaded with a USB bootloader and works with tools like Arduino IDE.

By default, this MCU is flashed with the [Tasmota](https://tasmota.github.io) IoT framework, enabling support for [a wide range of sensors and actuators](https://tasmota.github.io/docs/Supported-Peripherals/).

Users must configure Tasmota to use the pins exposed via three Grove ports.  
Other custom firmware can also be used, as the ESP32-C3 features built-in USB.

### 9.1 GPIO Ports

<img width="294" height="366" alt="image" src="https://github.com/user-attachments/assets/94563ff5-1bbd-4cfb-9759-a8fd37d2c003" />

There are two green Grove ports that expose two GPIOs each.

### 9.2 I2C Port

<img width="314" height="170" alt="image" src="https://github.com/user-attachments/assets/662d0d71-d0d9-4275-b125-e2deffde00f3" />

This purple Grove port exposes the I2C bus.

---

## 10. RGB LEDs

<img width="781" height="786" alt="image" src="https://github.com/user-attachments/assets/9e7b2acf-8857-4a0e-952a-a755b8fb0efd" />

The GoGo board uses 15 daisy-chained WS2812B RGB LEDs to visualize various board functionalities.
- Twelve 2.1 mm LEDs (2121 Package) are used for the Analog, Servo, DC motor ports.
- Three 3.5 mm LEDs (3535 Package) are used for the "code run" animation above the LCD display.

The driving signal is connected to the NEOPIXELS pin on the ESP32-S3.

Additional components:
- There is a 3.3 to 5 V level shifter (74AHCT1G125GV) for stable logic signals.
- A 470 Ohm noise rejection serial resistor is placed in the data line.

---

## 11. 1.8 Inch LCD Display

<img width="419" height="299" alt="image" src="https://github.com/user-attachments/assets/405d1d10-0d78-42d0-9b1b-7fc99acd0d5d" />

The GoGo Board uses a 1.8 inch TFT LCD screen with an SPI serial interface connected to the ESP32-S3. The driver chip is the ST7735S.

<img width="459" height="242" alt="image" src="https://github.com/user-attachments/assets/3528b0c6-3805-4983-a07c-031bb8fac398" />

There is a brightness dimming circuit via a MOSFET driver, allowing software control of screen brightness. The LCD_BRIGHTNESS pin is connected to the ESP32-S3.

---
