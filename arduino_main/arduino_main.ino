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
    print_int16(data[i]);
    Serial.print("  ");
    data[i] = 0;
  }

  Serial.println();
}



/*
void setup() {
  Wire.begin();
  Serial.begin(9600);
      Wire.beginTransmission( 0x68 );
    Wire.write( 0x3E );
    Wire.write( 0x00 );
    Wire.endTransmission();
    
    Wire.beginTransmission( 0x68 );
    Wire.write( 0x15 );
    Wire.write( 0x07 );
    Wire.endTransmission();
    
    Wire.beginTransmission( 0x68 );
    Wire.write( 0x16 );
    Wire.write( 0x1E );                         // +/- 2000 dgrs/sec, 1KHz, 1E, 19
    Wire.endTransmission();
    
    Wire.beginTransmission( 0x68 );
    Wire.write( 0x17 );
    Wire.write( 0x00 );
Wire.endTransmission();
}
void loop() {
      Wire.beginTransmission( 0x68 );
    Wire.write( 0x1B );
    Wire.endTransmission();
    
    Wire.beginTransmission( 0x68 );
    Wire.requestFrom( 0x68, 8 );             // request 8 bytes from ITG3200
    
    int i = 0;
    uint8_t buff[8];
    while(Wire.available())
    {
        buff[i] = Wire.read();
        i++;
    }
    Wire.endTransmission();
    
    print_int16((buff[4] << 8) | buff[5]);
    Serial.print("|");
    print_int16((buff[2] << 8) | buff[3]);
    Serial.print("|");
    print_int16((buff[6] << 8) | buff[7]);
    Serial.print("|");
    print_int16((buff[0] << 8) | buff[1]);
    Serial.println();
}
*/

