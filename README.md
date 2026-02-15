# Smart Algae Panel Data Logger

Arduino-based environmental monitoring firmware developed for:

**Analyzing the Effects of Smart Algae (Chlorophyta) Panels for Thermal Heat Index Reduction**

## Features
- CO2 measurement via SCD40
- Temperature & humidity logging
- Analog pH RAW signal acquisition
- I2C LCD display output
- Serial monitor data logging

## Hardware
- Arduino Uno
- SCD40 Sensor
- PH-4502C pH Module
- 16x2 I2C LCD

## Wiring
See:
- Wiring_Diagram.png
- Turnover Manual (DOCX)

## Usage
1. Install Arduino IDE
2. Install required libraries:
   - SparkFun SCD4x Arduino Library
   - LiquidCrystal I2C
3. Upload firmware
4. Open Serial Monitor (9600 baud)
