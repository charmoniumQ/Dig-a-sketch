#include "ITG3200.h"

// Datasheet: https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf

ITG3200::ITG3200() { }

ITG3200::ITG3200(const ITG3200 &other) {
  device = other.device;
}

ITG3200::ITG3200(bool setupI2C, bool first) {
  // See section 8.1 of datasheet
  if (first) {
    device = I2CDevice(DEFAULT_ADDRESS, setupI2C);
  } else {
    device = I2CDevice(DEFAULT_ADDRESS | 1, setupI2C);
  }
}

uint16_t ITG3200::set_frequency(ITG3200::Frequency low_pass_freq, uint8_t num_averaging) {
  device.set_register<uint8_t>(PWR_MGM, 0);
  device.set_register<uint8_t>(SMPLRT_DIV, num_averaging - 1);
  uint8_t DLPF_CFG = static_cast<uint8_t>(low_pass_freq);
  uint8_t FS_SEL = 3;
  device.set_register<uint8_t>(DLPF_FS, FS_SEL << 3 | DLPF_CFG); // TODO: Can I precompute this?
  
  // See section 8.2 of datasheet
  uint16_t internal_frequency;
  if (low_pass_freq == F_256_HZ) {
    internal_frequency = 8000;
  } else {
    internal_frequency = 1000;
  }
  return internal_frequency / num_averaging;
}

void ITG3200::get_data(double data[4]) {
  int8_t buff[8];
  // I would type-cast data (array of shorts) into an array of bytes,
  // but I can't garuntee endianness
  device.get_registers<int8_t>(TEMP_OUT_H, 8, buff);
  for (uint8_t i = 0; i < 4; ++i) {
    data[i] = (buff[2*i] << 8 | buff[2*i + 1]) * DEG_PER_LSB;
  }
}


bool ITG3200::good() { return device.good(); }

