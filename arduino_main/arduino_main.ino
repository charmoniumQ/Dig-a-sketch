#include "ITG3200.h"
#include "lib.h"

ITG3200 gyro;
int16_t data[4];

void setup() {
  Serial.begin(9600);

  gyro = ITG3200(true); // really initialize
  uint16_t f = gyro.set_frequency(ITG3200::F_5_HZ, 8);
  Serial.print("Frequency: ");
  Serial.println(f);
}

void loop() {
  delay(150);
  
  gyro.get_data(data);
  for (uint8_t i = 0; i < 4; ++i) {
    String str (data[i]);
    Serial.print(str);
    String padding = mulitply(" ", 8 - str.length());
    Serial.print(padding);
    data[i] = 0;
  }

  Serial.println();
}

