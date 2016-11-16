#ifndef ADXL345_H
#define ADXL345_H

#include <stdint.h>
#include "I2CDevice.h"

/*
 * Control the ADXL345 over the I2C bus
 * Datasheet http://www.analog.com/media/en/technical-documentation/data-sheets/ADXL345.pdf
 */
class ADXL345 {
public:
  /*
   * No-arg constructor
   * Reserves space in memory, but doesn't initialize anything
   * Must initialize with a copy constructor before use
   */
  ADXL345();
  
  /*
   * Copy constructor
   */
  ADXL345(const ADXL345& other);

  /*
   *  If set to true, the constructor will call Wire.begin
   *  Since Wire.begin should only be called once, set this to false
   *  if you are calling Wire.begin somewhere else in your code
   */
  ADXL345(bool setupI2C);

  /*
   * Gets the data. nuff said.
   */
  void get_data(int16_t data[3]);

  void set_power();

  enum Range {R_2G, R_4G, R_8G, R_16G};

  void set_range(Range range);

  enum Frequency {F_0_10_HZ, F_0_20_HZ, F_0_39_HZ, F_0_78_HZ, F_1_56_HZ, F_3_13_HZ, F_6_25_HZ, F_12_5_HZ, F_25_HZ, F_50_HZ, F_100_HZ, F_200_HZ, F_400_HZ, F_800_HZ, F_1600_HZ, F_3200_HZ};

  /*
   * See "Power Savings" in the data sheet
   */
  void set_frequency(Frequency data_rate, bool low_power = false);

  /*
   * Call after each operation to make sure the state is still good
   * This will be false if the communication fails in a detectable way
   */
  bool good();

protected:
  I2CDevice device;
  
  static const uint8_t DEFAULT_ADDRESS = 0x53;

  // See table 19 in data sheet
  static const I2CDevice::RegisterAddress DEVID          = 0x00;
  static const I2CDevice::RegisterAddress THRESH_TAP     = 0x1D;
  static const I2CDevice::RegisterAddress OFSX           = 0x1E;
  static const I2CDevice::RegisterAddress OFSY           = 0x1F;
  static const I2CDevice::RegisterAddress OFSZ           = 0x20;
  static const I2CDevice::RegisterAddress DUR            = 0x21;
  static const I2CDevice::RegisterAddress LATENT         = 0x22;
  static const I2CDevice::RegisterAddress WINDOW         = 0x23;
  static const I2CDevice::RegisterAddress THRESH_ACT     = 0x24;
  static const I2CDevice::RegisterAddress THRESH_INACT   = 0x25;
  static const I2CDevice::RegisterAddress TIME_INACT     = 0x26;
  static const I2CDevice::RegisterAddress ACT_INACT_CTL  = 0x27;
  static const I2CDevice::RegisterAddress THRESH_FF      = 0x28;
  static const I2CDevice::RegisterAddress TIME_FF        = 0x29;
  static const I2CDevice::RegisterAddress TAP_AXES       = 0x2A;
  static const I2CDevice::RegisterAddress ACT_TAP_STATUS = 0x2B;
  static const I2CDevice::RegisterAddress BW_RATE        = 0x2C;
  static const I2CDevice::RegisterAddress POWER_CTL      = 0x2D;
  static const I2CDevice::RegisterAddress INT_ENABLE     = 0x2E;
  static const I2CDevice::RegisterAddress INT_MAP        = 0x2F;
  static const I2CDevice::RegisterAddress INT_SOURCE     = 0x30;
  static const I2CDevice::RegisterAddress DATA_FORMAT    = 0x31;
  static const I2CDevice::RegisterAddress DATAX0         = 0x32;
  static const I2CDevice::RegisterAddress DATAX1         = 0x33;
  static const I2CDevice::RegisterAddress DATAY0         = 0x34;
  static const I2CDevice::RegisterAddress DATAY1         = 0x35;
  static const I2CDevice::RegisterAddress DATAZ0         = 0x36;
  static const I2CDevice::RegisterAddress DATAZ1         = 0x37;
  static const I2CDevice::RegisterAddress FIFO_CTL       = 0x38;
  static const I2CDevice::RegisterAddress FIFO_STATUS    = 0x39;
};

#endif

