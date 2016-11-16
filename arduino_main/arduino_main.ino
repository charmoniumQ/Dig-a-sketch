#include <Wire.h>
#include "ITG3200.h"
#include "ADXL345.h"

/*
 * Board pins to Arduino pins
 * SDA -> A4
 * SCL -> A5
 * Vin -> 3v3
 * 3v3 -> 3v3
 * GND -> GND
 */

const int BAUD = 9600;
const int DELAY = 500;

ITG3200 gyro;
ADXL345 accel;
double data1[4];
int16_t data2[3];

void setup() {
  Serial.begin(BAUD);
  Wire.begin();

  gyro = ITG3200(false); // really initialize
  uint16_t f = gyro.set_frequency(ITG3200::F_5_HZ, 8);
  Serial.print("Frequency: ");
  Serial.println(f);

  accel = ADXL345(false); // really initialize
  accel.set_range(ADXL345::R_4G);
  accel.set_frequency(ADXL345::F_25_HZ);
  accel.set_power();
}

void loop() {
  delay(DELAY);

  gyro.get_data(data1);
  accel.get_data(data2);
  for (uint8_t i = 0; i < 4; ++i) {
    String str (data1[i]);
    Serial.print(str);
    for (uint8_t j = 0; j < 8 - str.length(); ++j) {
      Serial.print(' ');
    }
    data1[i] = 0;
  }
  for (uint8_t i = 0; i < 3; ++i) {
    String str (data2[i]);
    Serial.print(str);
    for (uint8_t j = 0; j < 8 - str.length(); ++j) {
      Serial.print(' ');
    }
    data2[i] = 0;
  }
  Serial.println();
}

