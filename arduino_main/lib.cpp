#include "lib.h"

String mulitply(String in, int8_t reps) {
  String out;
  out.reserve(in.length() * reps);

  for (uint8_t i = 0; i < reps; ++i) {
    out += in;
  }
  return out;
}

