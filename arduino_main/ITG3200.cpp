#include "ITG3200.h"

// Datasheet: https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf

ITG3200::ITG3200() { }

ITG3200::ITG3200(const ITG3200 &other) {
  error = other.error;
  slave_address = other.slave_address;
}

ITG3200::ITG3200(boolean flag, boolean setupI2C, boolean first) {
  error = 0;
  if (setupI2C) {
    Wire.begin();
  }
  // See section 8.1 of datasheet
  if (first) {
    slave_address = DEFAULT_ADDRESS;
  } else {
    slave_address = DEFAULT_ADDRESS | 1;
  }
}

uint16_t ITG3200::set_frequency(ITG3200::Frequency low_pass_freq, uint8_t num_averaging) {
  set_register(PWR_MGM, 0);
  set_register(SMPLRT_DIV, num_averaging - 1);
  uint8_t DLPF_CFG = (uint8_t) low_pass_freq;
  uint8_t FS_SEL = 3;
  set_register(DLPF_FS, FS_SEL << 3 | DLPF_CFG); // TODO: Can I precompute this?
  
  // See section 8.2 of datasheet
  uint16_t internal_frequency;
  if (low_pass_freq == F_256_HZ) {
    internal_frequency = 8000;
  } else {
    internal_frequency = 1000;
  }
  return internal_frequency / num_averaging;
}

void ITG3200::get_data(int16_t (&data)[4]) {
  uint8_t buff[8];
  // I would type-cast data (array of shorts) into an array of bytes,
  // but I can't garuntee endianness
  get_register(TEMP_OUT_H, 8, buff);
  for (uint8_t i = 0; i < 8; ++i) {
    if (i % 2 == 0) {
      // set high byte (and clear remaining data)
      data[i / 2] = buff[i] << 8;
    } else {
      // set low byte
      data[i / 2] |= buff[i];
    }
  }
}

void ITG3200::get_register(RegisterAddress reg, uint8_t quantity, uint8_t * buff) {
  // Tutorial: https://www.arduino.cc/en/Tutorial/MasterReader
  error = 0;
  Wire.beginTransmission(slave_address); {
    Wire.write(reg);
  } Wire.endTransmission();
  
  Wire.beginTransmission(slave_address); {
    Wire.requestFrom(slave_address, quantity);
    for (uint8_t i = 0; i < quantity; ++i) {
      if (Wire.available()) {
        buff[i] = Wire.read();
      } else {
        error = 1;
        break;
      }
    }
  } Wire.endTransmission();

  #ifdef ITG3200_DEBUG
    for (uint8_t i = 0; i < quantity; ++i) {
     Serial.print(slave_address);
      Serial.print(": R[");
      Serial.print(reg);
      Serial.print(" + ");
      Serial.print(i);
      Serial.print("] == ");
      Serial.print(buff[i]);
      Serial.print("  (");
      Serial.print(error);
      Serial.print(")");
      Serial.println();
    }
  #endif
}

void ITG3200::set_register(RegisterAddress reg, byte input) {
  // Tutorial: https://www.arduino.cc/en/Tutorial/MasterWriter

  #ifdef ITG3200_DEBUG
    Serial.print(slave_address);
    Serial.print(": R[");
    Serial.print(reg);
    Serial.print("] := ");
    Serial.print(input);
    Serial.println();
  #endif
  
  Wire.beginTransmission(slave_address); {
    Wire.write(reg);
    Wire.write(input);
  } Wire.endTransmission(slave_address);
}

bool ITG3200::good() { return error == 0; }

