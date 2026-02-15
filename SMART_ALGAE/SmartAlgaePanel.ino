/*
  ==========================================================
  SMART ALGAE PANEL – DATA ACQUISITION FIRMWARE
  ==========================================================

  Title:
  Analyzing the Effects of Smart Algae (Chlorophyta) Panels
  for Thermal Heat Index Reduction

  Board:
  Arduino Uno

  Sensors:
    - SCD40  : CO2, Temperature, Humidity (I2C)
    - PH-4502C : Analog pH Probe (RAW signal only)
    - 16x2 LCD : I2C Display for local monitoring
    
  ----------------------------------------------------------
  RESEARCH NOTE:
  This firmware ONLY collects RAW environmental data.

  The system intentionally DOES NOT:
    - Compute pH values
    - Calculate heat index
    - Perform statistical analysis

  All scientific analysis must be performed externally
  (Excel, Python, research tools, etc.).

  ----------------------------------------------------------
  PROPONENTS:
    Evangelista, Mc Denver E.
    Esmeria, Grace Ann S.
    Espiritu, Ashanie Mae G.

  PROGRAMMER / DEVELOPER:
    Karl Santiago Bernaldez

  Research Adviser:
    Ms. May Ann D. Romano

  Institution:
    Pasay City South High School
  ==========================================================
*/

#include <Wire.h>
#include <SparkFun_SCD4x_Arduino_Library.h>
#include <LiquidCrystal_I2C.h>

/* =========================================================
   HARDWARE CONFIGURATION
   ========================================================= */

// Analog pin for pH module output
#define PH_PIN A0

// Arduino UNO ADC reference and resolution
#define ADC_REF 5.0 // maximum measurable voltage
#define ADC_RESOLUTION 1023.0 //maximum ADC reading

/* =========================================================
   OBJECT INSTANTIATION
   ========================================================= */

// SCD40 environmental sensor object
SCD4x scd40;

// LCD object (default address 0x27, change to 0x3F if needed)
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* =========================================================
   GLOBAL VARIABLES
   ========================================================= */

// Timing control for periodic sensor reading
unsigned long lastReadTime = 0;
const unsigned long READ_INTERVAL = 5000; // milliseconds (5 sec)

// Environmental readings
float co2 = 0;
float temperature = 0;
float humidity = 0;

// pH sensor raw values
int phRaw = 0;
float phVoltage = 0;

// LCD screen cycling state
int screenState = 0;

/* =========================================================
   SETUP FUNCTION
   Runs once during power-on or reset
   ========================================================= */
void setup() {

  // Initialize serial communication for logging
  Serial.begin(9600);

  // Initialize I2C bus (UNO uses SDA=A4, SCL=A5)
  Wire.begin();

  // Initialize display and sensors
  initializeLCD();
  initializeSCD40();

  Serial.println("System Initialized.");
}

/* =========================================================
   MAIN LOOP
   Runs continuously after setup()
   ========================================================= */
void loop() {

  unsigned long currentTime = millis();

  // Read sensors only at defined interval
  if (currentTime - lastReadTime >= READ_INTERVAL) {

    lastReadTime = currentTime;

    readAirSensors();   // CO2, temperature, humidity
    readPHSensor();     // raw analog pH signal
    printSerialOutput();// send formatted data to PC
    updateLCD();        // update local display
  }
}

/* =========================================================
   INITIALIZATION FUNCTIONS
   ========================================================= */

/*
  Initializes LCD and shows startup message.
*/
void initializeLCD() {

  lcd.init();
  lcd.backlight();

  // --- Splash Screen ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SMART ALGAE");
  lcd.setCursor(0, 1);
  lcd.print("PANEL SYSTEM");
  delay(2000);

  // --- Firmware Loading ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Firmware Boot");
  lcd.setCursor(0, 1);
  lcd.print("Loading...");
  delay(1500);

  // --- System Ready Message ---
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Initializing");
  lcd.setCursor(0, 1);
  lcd.print("Sensors...");
  delay(1500);

  lcd.clear();
}

/*
  Initializes the SCD40 sensor.
  If sensor is not detected, system halts to prevent
  recording invalid research data.
*/
void initializeSCD40() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Init SCD40...");

  if (!scd40.begin()) {

    lcd.setCursor(0, 1);
    lcd.print("Sensor Error!");

    // Stop execution if sensor missing
    while (1);
  }

  // Start continuous measurement mode
  scd40.startPeriodicMeasurement();

  delay(2000);
  lcd.clear();
}

/* =========================================================
   SENSOR READING FUNCTIONS
   ========================================================= */

/*
  Reads environmental data from SCD40.
  Updates global variables only if a new
  measurement is available.
*/
void readAirSensors() {

  if (scd40.readMeasurement()) {

    co2 = scd40.getCO2();
    temperature = scd40.getTemperature();
    humidity = scd40.getHumidity();
  }
}

/*
  Reads RAW analog signal from pH module
  and converts it to voltage.

  NOTE:
  No pH conversion formula applied intentionally.
*/
void readPHSensor() {

  phRaw = analogRead(PH_PIN);
  phVoltage = phRaw * (ADC_REF / ADC_RESOLUTION);
}

/* =========================================================
   OUTPUT FUNCTIONS
   ========================================================= */

/*
  Sends formatted sensor data to Serial Monitor.
  Used for:
    - Data logging
    - Experiment recording
    - External processing
*/
void printSerialOutput() {

  Serial.print("CO2: ");
  Serial.print(co2);
  Serial.print(" ppm | Temp: ");
  Serial.print(temperature, 2);
  Serial.print(" C | RH: ");
  Serial.print(humidity, 2);
  Serial.print(" % | pH RAW: ");
  Serial.print(phRaw);
  Serial.print(" | Voltage: ");
  Serial.print(phVoltage, 3);
  Serial.println(" V");
}

/*
  Updates LCD display.

  Screen 0:
    CO2 + Temperature + Humidity

  Screen 1:
    pH raw value + voltage

  Display alternates every sensor cycle.
*/
void updateLCD() {

  lcd.clear();

  if (screenState == 0) {

    lcd.setCursor(0, 0);
    lcd.print("CO2:");
    lcd.print(co2);
    lcd.print("ppm");

    lcd.setCursor(0, 1);
    lcd.print("T:");
    lcd.print(temperature, 1);
    lcd.print("C H:");
    lcd.print(humidity, 0);
    lcd.print("%");
  }

  else if (screenState == 1) {

    lcd.setCursor(0, 0);
    lcd.print("pH RAW:");
    lcd.print(phRaw);

    lcd.setCursor(0, 1);
    lcd.print("Volt:");
    lcd.print(phVoltage, 2);
    lcd.print("V");
  }

  // Toggle screen state
  screenState++;
  if (screenState > 1) screenState = 0;
}
