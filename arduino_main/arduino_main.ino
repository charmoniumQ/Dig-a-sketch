#include <Wire.h>
#include "ITG3200.h"
#include "ADXL345.h"

ITG3200 gyro;
ADXL345 accel;
int16_t data[7];

void setup() {
  Serial.begin(9600);
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
  delay(150);
  
  gyro.get_data(&data[0]);
  accel.get_data(&data[4]);
  for (uint8_t i = 0; i < 7; ++i) {
    String str (data[i]);
    Serial.print(str);
    for (uint8_t i = 0; i < 8 - str.length(); ++i) {
      Serial.print(' ');
    }
    data[i] = 0;
  }
  Serial.println();
}

