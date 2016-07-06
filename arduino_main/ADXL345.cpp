#include "ADXL345.h"

ADXL345::ADXL345() { }

ADXL345::ADXL345(const ADXL345& other) : device(other.device) { }

ADXL345::ADXL345(bool setupI2C) : device(DEFAULT_ADDRESS, setupI2C) { }

void ADXL345::set_power() {
  device.set_register(POWER_CTL, 1 << 3);
}

void ADXL345::set_range(Range range) {
  device.set_register(DATA_FORMAT, static_cast<uint8_t>(range));
}

void ADXL345::set_frequency(Frequency data_rate, bool low_power) {
  uint8_t val = data_rate | static_cast<int>(low_power) << 4;
  device.set_register(BW_RATE, val);
}

void ADXL345::get_data(int16_t data[3]) {
  int8_t temp_data[6];
  device.get_registers<int8_t>(DATAX0, 6, temp_data);
  for (int i = 0; i < 3; ++i) {
    data[i] = temp_data[2*i] | temp_data[2*i + 1] << 8;
  }
}

bool ADXL345::good() {
  return device.good();
}

