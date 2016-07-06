#include "I2CDevice.h"
#include <Wire.h>
#ifdef I2C_DEBUG
  #include <Arduino.h>
#endif

I2CDevice::I2CDevice() { }

I2CDevice::I2CDevice(uint8_t address_, bool setupI2C) : address(address_) {
  if (setupI2C) {
    Wire.begin();
  }
  clear_error();
}

I2CDevice::I2CDevice(const I2CDevice &other) : address(other.address), error(other.error) { }

/*
int8_t I2CDevice::operator[](RegisterAddress reg) {
  return get_register_int8(reg);
}
*/

void I2CDevice::get_registers_uint8(RegisterAddress reg, uint8_t quantity, uint8_t * out_buf) {
  clear_error();
  Wire.beginTransmission(address); {
    Wire.write(reg);
  } Wire.endTransmission();
  
  Wire.beginTransmission(address); {
    Wire.requestFrom(address, quantity);
    for (uint8_t i = 0; i < quantity; ++i) {
      if (Wire.available()) {
        out_buf[i] = Wire.read();
      } else {
        set_incomplete_data_error();
        break;
      }
    }
  } Wire.endTransmission();

  #ifdef I2C_DEBUG
    for (uint8_t i = 0; i < quantity; ++i) {
      Serial.print(address);
      Serial.print(": reg[");
      Serial.print(reg + i);
      Serial.print("] == ");
      Serial.print(out_buf[i]);
      Serial.println(is_incomplete_data_error() ? " incomplete" : "");
    }
  #endif
}

uint8_t I2CDevice::get_register_uint8(RegisterAddress reg) {
  clear_error();
  Wire.beginTransmission(address); {
    Wire.write(reg);
  } Wire.endTransmission();

  int8_t out;
  Wire.beginTransmission(address); {
    Wire.requestFrom(address, (uint8_t) 1);
    if (Wire.available()) {
      out = Wire.read();
    } else {
      set_incomplete_data_error();
    }
  } Wire.endTransmission();

  #ifdef I2C_DEBUG
    Serial.print(address);
    Serial.print(": reg[");
    Serial.print(reg);
    Serial.print("] == ");
    Serial.println(out);
  #endif
  
  return out;
}

void I2CDevice::set_register_uint8(RegisterAddress reg, uint8_t value) {
  clear_error();
  Wire.beginTransmission(address); {
    Wire.write(reg);
    Wire.write(value);
  } Wire.endTransmission();

  #ifdef I2C_DEBUG
    Serial.print(address);
    Serial.print(": reg[");
    Serial.print(reg);
    Serial.print("] := ");
    Serial.println(value);
  #endif
}

bool I2CDevice::good() {
  return error == 0;
}

void I2CDevice::clear_error() {
  error = 0;
}

bool I2CDevice::is_incomplete_data_error() {
  return (error & 1) != 0;
}

void I2CDevice::set_incomplete_data_error() {
  error |= 1;
}

