#include <Wire.h> // enables I2C communication
#include <Adafruit_ADS1X15.h> // provides functions to control the ADS1115

Adafruit_ADS1115 ads; // Create an instance(ads) of the ADS1115

void setup(void) {
  Serial.begin(9600); // baud: bits per second
  Serial.println("Starting ADS1115...");

  if (!ads.begin()) {
    Serial.println("ADS1115 not found. Check wiring!");
    while (1); // Stop if the device isn't found
  }

  // Set gain (adjust based on expected input range)
  ads.setGain(GAIN_ONE);  // set ±4.096V range, 0.125 mV/bit
} 

void loop(void) {
  int16_t raw = ads.readADC_SingleEnded(0); // Read A0
  // 16 bits range: total = 65,536 (-32,768 to 32,767)
  float voltage = (raw * 0.125) / 1000.0;
  // raw * 0.125: to get millivolts
  // Divide by 1000: convert millivolts to volts

  Serial.print("AIN0: ");
  Serial.print(raw);
  Serial.print("\t");
  Serial.print(voltage, 4); // the converted voltage, formatted to 4 decimal places
  Serial.println(" V");

  delay(1000); // Waits for 1 second
}
