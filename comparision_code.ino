#include <Wire.h> // enables I2C communication
#include <Adafruit_ADS1X15.h> // provides functions to control the ADS1115

Adafruit_ADS1115 ads; // Create an instance(ads) of the ADS1115

const int dueAnalogPin = A0;  // Arduino Due analog input pin

void setup(void) {
  Serial.begin(9600); // baud: bits per second

  if (!ads.begin()) {
    Serial.println("ADS1115 not found. Check wiring!");
    while (1); // Stop if the device isn't found
  }

  // Set gain (adjust based on expected input range)
  ads.setGain(GAIN_ONE);  // set ±4.096V range, 0.125 mV/bit
}

void loop(void) {
  // Read Due's internal 12-bit ADC (0–4095)
  int dueRaw = analogRead(dueAnalogPin); // Reads the analog voltage at pin A0
  float dueVoltage = (dueRaw * 3.3) / 4095.0;  // Due uses 3.3V reference

  // Read ADS1115 (0–32767 for single-ended)
  int16_t adsRaw = ads.readADC_SingleEnded(0); //  Reads analog voltage from ADS1115 Channel AIN0
  float adsVoltage = adsRaw * 0.125 / 1000.0;
  // raw * 0.125: to get millivolts
  // Divide by 1000: convert millivolts to volts

  // Print both for Serial Plotter
  Serial.print(dueVoltage, 4);
  Serial.print("\t");
  Serial.println(adsVoltage, 4);

  delay(1000);  // Faster refresh for smoother graph
}

