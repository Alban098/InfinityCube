#pragma once
#include "Params.h"

struct Point {
  uint8_t x;
  uint8_t y;
  uint8_t z;

  Point(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}
};

class Mapping {
  public:
    static const Point points[Params::NUM_PIXELS];
};
