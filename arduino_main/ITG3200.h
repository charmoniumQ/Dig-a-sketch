#ifndef ITG3200_H
#define ITG3200_H

#include <Wire.h>
#include "I2CDevice.h"

//#define ITG3200_DEBUG

/*
 * Control the gyro ITG3200 over the I2C bus
 * Datasheet https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf
 */
class ITG3200 {
public:

  /*
   * No-arg constructor
   * Must re-initialize with an assignment/copy constructor before use
   */
  ITG3200();
  
  /*
   * Copy constructor
   */
  ITG3200(const ITG3200& other);

  /*
   * If setupI2C is true, then Wire.begin is called. Since this should be called only once
   * in your sketch, If you call Wire.begin somewhere else, set setupI2C to false.
   * If there are multiple ITG3200 chips on the I2C bus, you can differeniate between them changing
   * pin 9. In software the one with pin 9 low is first=true. Then one with pin 9 high is first=false.
   * See section 6.1.1 of the datasheet.
   */
  ITG3200(bool setupI2C, bool first=true);
  
  /*
   * Call after each operation to make sure the state is still good
   * This will be false if the communication fails in a detectable way
   */
  bool good();

  /*
   * Frequency choices for the internal low pass filter (used in set_frequency)
   */
  enum Frequency {F_256_HZ, F_188_HZ, F_98_HZ, F_42_HZ, F_20_HZ, F_10_HZ, F_5_HZ};

  /*
   * low_pass_freq sets the frequency for the internal low pass filter
   * num_averaging is the number of additional readings to save and average
   * returns the external sampling frequency
   */
  uint16_t set_frequency(Frequency low_pass_freq, uint8_t num_averaging);

  /*
   * data[0] = temperature, data[1] = gyro x, data[2] = gyro y, data[3] = gyro z
   */
  void get_data(int16_t (&data)[4]);

protected:
  I2CDevice device;
  
  static const uint8_t DEFAULT_ADDRESS = 0x68;

  // See section 7 in the datasheet
  static const I2CDevice::RegisterAddress WHO_AM_I    = 0x00;
  static const I2CDevice::RegisterAddress SMPLRT_DIV  = 0x15;
  static const I2CDevice::RegisterAddress DLPF_FS     = 0x16;
  static const I2CDevice::RegisterAddress INT_CFG     = 0x17;
  static const I2CDevice::RegisterAddress INT_STATUS  = 0x1A;
  static const I2CDevice::RegisterAddress TEMP_OUT_H  = 0x1B;
  static const I2CDevice::RegisterAddress TEMP_OUT_L  = 0x1C;
  static const I2CDevice::RegisterAddress GYRO_XOUT_H = 0x1D;
  static const I2CDevice::RegisterAddress GYRO_XOUT_L = 0x1E;
  static const I2CDevice::RegisterAddress GYRO_YOUT_H = 0x1F;
  static const I2CDevice::RegisterAddress GYRO_YOUT_L = 0x20;
  static const I2CDevice::RegisterAddress GYRO_ZOUT_H = 0x21;
  static const I2CDevice::RegisterAddress GYRO_ZOUT_L = 0x22;
  static const I2CDevice::RegisterAddress PWR_MGM     = 0x3E;
};

#endif
