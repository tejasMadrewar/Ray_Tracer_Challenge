#ifndef CANVAS_H
#define CANVAS_H

#include "./color.h"
#include <fstream>
#include <vector>

#define DEBUG_canvas 0

class canvas {
public:
  canvas();
  ~canvas() {}

  canvas(const canvas &can);
  canvas(int W, int H);
  int width() const { return Width; }
  int height() const { return Height; }
  color pixel_at(const int w, const int h) const;
  void write_pixel(const int w, const int h, const color col);
  int canvas_to_ppm(std::string filename = "OUTPUT.ppm", int max = 255);

  inline int fix_range(float oldValue) {
    int newValue = ceil(oldValue * 255);
    if (oldValue < 0)
      newValue = 0;
    if (oldValue > 1)
      newValue = 255;
#if DEBUG_canvas_1
    std::cout << " oldValue: " << oldValue << " newValue : " << newValue
              << "\n";
#endif
    return newValue;
  }

private:
  int Width, Height;
  // color *arr = nullptr;
  std::vector<color> arr;
};

#endif
