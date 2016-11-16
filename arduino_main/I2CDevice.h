#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include <stdint.h>

// #define I2C_DEBUG

/*
 * OOP-style library for talking to an I2C device (one per object)
 */
class I2CDevice {
public:
  /*
   * Reserve memory for an I2C device, but don't put anything there yet
   * Must initialize with a copy constructor later on
   */
  I2CDevice();

  /*
   * Create a new device with the given address
   * If setupI2C is true (default), then Wire.begin is called. Since this should be called only once
   * in your sketch, If you call Wire.begin somewhere else, set setupI2C to false.
   */
  I2CDevice(uint8_t address, bool setupI2C=true);

  /*
   * Copy constructor
   */
  I2CDevice(const I2CDevice &other);

  /*
   * Datatype to be used for holding an address
   * Declare all registers you intend to access with this datatype
   */
  typedef uint8_t RegisterAddress;

  /*
   * Read a single register and cast it to type T
   */
  template <typename T>
  T get_register(RegisterAddress reg) {
    uint8_t val = get_register_uint8(reg);
    return reinterpret_cast<T&>(val);
  }

  /*
   * Read a single register
   * TODO: return a reference that is assingable
   */
  //int8_t operator[](RegisterAddress reg);

  /*
   * Read a range of registers into the buffer
   */
  template <typename T>
  void get_registers(RegisterAddress reg, uint8_t quantity, T * out_buf) {
    get_registers_uint8(reg, quantity, reinterpret_cast<uint8_t*>(out_buf));
  }

  /*
   * Set a single register
   */
  template <typename T>
  void set_register(RegisterAddress reg, T value) {
    uint8_t value2  = reinterpret_cast<uint8_t&>(value);
    set_register_uint8(reg, value2);
  }

  /*
   * False if the previous command failed in a detectible way
   */
  bool good();

  /*
   * True if the data stopped sending out data before the transmission was complete
   */
  bool is_incomplete_data_error();
  
private:
  uint8_t address;
  uint8_t error;

  void clear_error();
  void set_incomplete_data_error();
  
  void get_registers_uint8(RegisterAddress reg, uint8_t quantity, uint8_t * buf);
  uint8_t get_register_uint8(RegisterAddress reg);
  void set_register_uint8(RegisterAddress reg, uint8_t val);
};

#endif
