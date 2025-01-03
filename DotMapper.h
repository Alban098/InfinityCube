#pragma once
#include "Params.h"

struct Point {
  uint8_t x;
  uint8_t y;
  uint8_t z;

  Point(uint8_t x, uint8_t y, uint8_t z) : x(x), y(y), z(z) {}
};

struct Segment {
  uint8_t start_x;
  uint8_t start_y;
  uint8_t start_z;
  uint8_t end_x;
  uint8_t end_y;
  uint8_t end_z;
  
  Segment(uint8_t start_x, uint8_t start_y, uint8_t start_z, uint8_t end_x, uint8_t end_y, uint8_t end_z) : start_x(start_x), start_y(start_y), start_z(start_z), end_x(end_x), end_y(end_y), end_z(end_z) {}
};

class DotMapper {
  private:
    static const Segment segments[12];

  public:
    static Point map(uint16_t dot_index);
};
