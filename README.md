# **Smart Algae Panel System**

**Project:** Analyzing the Effects of Smart Algae (Chlorophyta) Panels for Thermal Heat Index Reduction

![Smart Algae Panel Wiring Diagram](./SmartAlgae.png)

# **1\. System Overview**

This system measures:  
 • CO2 concentration  
 • Temperature  
 • Humidity  
 • Raw pH sensor signal

 The Arduino collects RAW data only. All analysis must be done externally.

# **2\. Install Arduino IDE**

1\. Go to this link [Arduino](https://www.arduino.cc/en/software/#ide) or click this direct [link](https://downloads.arduino.cc/arduino-ide/arduino-ide_2.3.7_Windows_64bit.exe).  
 2\. Download Arduino IDE  
 3\. Install using default settings  
 4\. Launch Arduino IDE after installation

# **3\. Connect the Arduino**

1\. Plug Arduino Uno into computer using USB cable  
 2\. Open Arduino IDE  
 3\. Go to Tools → Board → Arduino Uno  
 4\. Go to Tools → Port → Select the COM port that appears

# **4\. Install Required Libraries**

In Arduino IDE:  
 1\. Click Sketch → Include Library → Manage Libraries  
 2\. Search and install:  
    • SparkFun SCD4x Arduino Library  
    • LiquidCrystal I2C by Frank de Brabander

# **5\. Wiring Instructions**

**SCD40 Sensor**:  
 VIN → Arduino 3.3V  
 GND → Arduino GND  
 SDA → Arduino A4  
 SCL → Arduino A5

 **I2C LCD**:  
 VCC → Arduino 5V  
 GND → Arduino GND  
 SDA → Arduino A4  
 SCL → Arduino A5

 **pH Sensor Module**:  
 V+ → Arduino 5V  
 G → Arduino GND  
 Po → Arduino A0

![Smart Algae Panel Wiring Diagram](./circuit_image.png)

*Smart Algae Panel Wiring Diagram shows the complete physical connections between the Arduino Uno, SCD40 sensor, I2C LCD, and pH module.*

# **6\. Upload the Firmware**

1\. Open the Smart Algae [firmware](https://drive.google.com/file/d/1yA7DHeMxdEHIfy_rZsVymDJe6al_NNXS/view?usp=sharing) (.ino file) (Go to File → Open→ SmartAlgaePanel.ino)  
 2\. Click Verify (✓)  
 3\. Wait for 'Done compiling'  
 4\. Click Upload (→)  
 5\. Wait for 'Done uploading'

# **7\. First Startup**

After upload:  
 • LCD shows splash screen  
 • Title scroll appears  
 • Sensor initializes  
 • Live readings begin

# **8\. Viewing Data**

To view readings on computer:  
 1\. Open Serial Monitor  
 2\. Set baud rate to 9600  
 3\. Observe data lines for CO2, temperature, humidity, and pH RAW

# **9\. Proper Handling of Sensors**

SCD40:  
 • Do not cover holes  
 • Avoid water splashes

 pH Probe:  
 • Fragile glass tip  
 • Do not drop  
 • Keep slightly moist if stored

 Wiring:  
 • Do not unplug while powered

# **10\. Troubleshooting**

LCD blank:  
 • Check wiring  
 • Adjust LCD contrast screw

 Upload fails:  
 • Check correct COM port  
 • Check USB cable

 Sensor error:  
 • Restart Arduino  
 • Check sensor wiring

# **11\. Shutdown Procedure**

1\. Close Serial Monitor  
 2\. Unplug USB cable safely  
 3\. Store sensors properly
