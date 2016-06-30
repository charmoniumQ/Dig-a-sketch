#include "lib.h"

void print_int16(int16_t s) {
         if (99999 >= s && s >= 10000) {
    Serial.print(" ");
    Serial.print(s);
  } else if (9999 >= s && s >= 1000) {
    Serial.print("  ");
    Serial.print(s);
  } else if (999 >= s && s >= 100) {
    Serial.print("   ");
    Serial.print(s);
  } else if (99 >= s && s >= 10) {
    Serial.print("    ");
    Serial.print(s);
  } else if (9 >= s && s >= 1) {
    Serial.print("     ");
    Serial.print(s);
  } else if (s == 0) {
    Serial.print("     ");
    Serial.print(s);
  } else if (-1 >= s && s >= -9) {
    Serial.print("    ");
    Serial.print(s);
  } else if (-10 >= s && s >= -99) {
    Serial.print("   ");
    Serial.print(s);
  } else if (-100 >= s && s >= -999) {
    Serial.print("  ");
    Serial.print(s);
  } else if (-1000 >= s && s >= -9999) {
    Serial.print(" ");
    Serial.print(s);
  } else if (-10000 >= s && s >= -99999) {
    Serial.print(s);
  } else {
    Serial.print(">");
    Serial.print(s);
  }
}
