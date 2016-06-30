#ifndef ITG3200_H
#define ITG3200_H

#include <Arduino.h>
#include <Wire.h>

//#define ITG3200_DEBUG

/*
 * Control the gyro ITG3200 over the I2C bus
 * Datasheet https://www.sparkfun.com/datasheets/Sensors/Gyro/PS-ITG-3200-00-01.4.pdf
 */
class ITG3200 {
public:
  /*
   * No-arg constructor
   */
  ITG3200();
  
  /*
   * Copy constructor
   */
  ITG3200(const ITG3200& other);

  /*
   * The flag parameter is to differentiate this from the no-arg constructor. It is not used.
   * If setupI2C is true (default), then Wire.begin is called. Since this should be called only once
   * in your sketch, If you call Wire.begin somewhere else, set setupI2C to false.
   * If there are multiple ITG3200 chips on the I2C bus, you can differeniate between them changing
   * pin 9. In software the one with pin 9 low is first=true. Then one with pin 9 high is first=false.
   * See section 6.1.1 of the datasheet.
   */
  ITG3200(bool flag, bool setupI2C=true, bool first=true);
  
  /*
   * Call after each operation to make sure the state is still good
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
  typedef uint8_t RegisterAddress;
  typedef uint8_t DeviceAddress;
  
  void get_register(RegisterAddress reg, uint8_t quantity, uint8_t * buf);
  void set_register(RegisterAddress reg, uint8_t val);
  
  DeviceAddress slave_address;
  
  uint8_t error;
  // if (error == 1) { ITG3200 did not send requested data }
  
  static const DeviceAddress DEFAULT_ADDRESS = B01101000;

  // See section 7 in the datasheet
  static const RegisterAddress WHO_AM_I = 0;
  static const RegisterAddress SMPLRT_DIV = 21;
  static const RegisterAddress DLPF_FS = 22;
  static const RegisterAddress INT_CFG = 23;
  static const RegisterAddress INT_STATUS = 26;
  static const RegisterAddress TEMP_OUT_H = 27;
  static const RegisterAddress TEMP_OUT_L = 28;
  static const RegisterAddress GYRO_XOUT_H = 29;
  static const RegisterAddress GYRO_XOUT_L = 30;
  static const RegisterAddress GYRO_YOUT_H = 31;
  static const RegisterAddress GYRO_YOUT_L = 32;
  static const RegisterAddress GYRO_ZOUT_H = 33;
  static const RegisterAddress GYRO_ZOUT_L = 34;
  static const RegisterAddress PWR_MGM = 62;

};

#endif
