#include "DotMapper.h"
#include <math.h>

const Segment DotMapper::segments[12] = {
  // Hardcoded for a Cube rotated to sit on one corner at coords (128, 128, 0)
  Segment(
    128, 128,   0,
    128, 248,  85
  ),
  Segment(
    128, 248,  85,
    232, 188, 170
  ),
  Segment(
    232, 188, 170,
    232,  67,  85
  ),
  Segment(
    232,  67,  85,
    128, 128,   0
  ),

  Segment(
     23, 188, 170,
    128, 248,  85
  ),
  Segment(
    128, 128, 255,
    232, 188, 170
  ),
  Segment(
    128,   8, 170,
    232,  68,  85
  ),
  Segment(
     24,  68,  85,
    128, 128,   0
  ),
  Segment(
     24,  68,  85,
     24, 188, 170
  ),
  Segment(
     24, 188, 170,
    128, 128, 255
  ),
  Segment(
    128, 128, 255,
    128,   8, 170
  ),
  Segment(
    128,   8, 170,
     24,  68,  85
  )
};

Point DotMapper::map(uint16_t dot_index) {
  Segment segment = DotMapper::segments[dot_index / 16];
  float percent = (dot_index % 16) / 16.0;
  return Point(
    segment.start_x + (segment.end_x - segment.start_x) * percent, 
    segment.start_y + (segment.end_y - segment.start_y) * percent, 
    segment.start_z + (segment.end_z - segment.start_z) * percent
  );
}