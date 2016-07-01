#include "I2CDevice.h"

I2CDevice::I2CDevice() { }

I2CDevice::I2CDevice(uint8_t address_, bool setupI2C) : address(address_) {
  if (setupI2C) {
    Wire.begin();
  }
  clear_error();
}

I2CDevice::I2CDevice(const I2CDevice &other) : address(other.address), error(other.error) { }

int8_t I2CDevice::operator[](RegisterAddress reg) {
    return get_register_int8(reg);
  }

void I2CDevice::get_registers_int8(RegisterAddress reg, uint8_t quantity, int8_t * out_buf) {
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
}

int8_t I2CDevice::get_register_int8(RegisterAddress reg) {
  clear_error();
  Wire.beginTransmission(address); {
    Wire.write(reg);
  } Wire.endTransmission();

  int8_t out;
  Wire.beginTransmission(address); {
    Wire.requestFrom(address, byte(1));
    if (Wire.available()) {
      out = Wire.read();
    } else {
      set_incomplete_data_error();
    }
  } Wire.endTransmission();
  return out;
}

void I2CDevice::set_register_int8(RegisterAddress reg, int8_t value) {
  clear_error();
  Wire.beginTransmission(address); {
    Wire.write(reg);
    Wire.write(value);
  } Wire.endTransmission();
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

