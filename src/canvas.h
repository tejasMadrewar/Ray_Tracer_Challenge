#ifndef CANVAS_H
#define CANVAS_H

#include "./color.h"
#include <fstream>
#include <vector>

#define DEBUG 0

class canvas {
private:
  int Width, Height;
  // color *arr = nullptr;
  std::vector<color> arr;

public:
  canvas() {
    Width = 0;
    Height = 0;
  }

  canvas(int W, int H) {
    Width = W;
    Height = H;
    arr.resize(Width * Height, color());
  }

  ~canvas() {}

  int width() const { return Width; }
  int height() const { return Height; }

  color pixel_at(const int w, const int h) const {
    return arr.at((h * Width) + w);
  }

  void write_pixel(const int w, const int h, const color col) {
    arr.at((h * Width) + w) = col;
  }

  // set range between 0 to 255
  inline int fix_range(float oldValue) {
    int newValue = ceil(oldValue * 255);
    if (oldValue < 0)
      newValue = 0;
    if (oldValue > 1)
      newValue = 255;
#if DEBUG
    std::cout << " oldValue: " << oldValue << " newValue : " << newValue
              << "\n";
#endif
    return newValue;
  }

  int canvas_to_ppm(std::string filename = "OUTPUT.ppm", int max = 255) {

#if DEBUG
    for (int i = 0; i < Height; i++) {
      for (int j = 0; j < Width; j++) {

        std::cout << "red: " << arr.at((i * Width) + j).red()
                  << " green: " << arr.at((i * Width) + j).green()
                  << " blue: " << arr.at((i * Width) + j).blue() << "\n";
      }
    }
#endif

    std::ofstream outf(filename.c_str(), std::ios::trunc);
    if (!outf) {
      return 0;
    }
    // header
    outf << "P3\n";
    outf << Width << " " << Height << "\n";
    outf << max << "\n";
    // body
    int counter = 0;
    for (int i = 0; i < Height; i++) {
      for (int j = 0; j < Width; j++) {
        outf

            << fix_range(arr.at((i * Width) + j).red()) << " "
            << fix_range(arr.at((i * Width) + j).green()) << " "
            << fix_range(arr.at((i * Width) + j).blue()) << " ";

        counter++;
        if (counter % 5 == 0) {
          outf << "\n";
        }
      }
      outf << "\n";
    }
    // compatability with imagemagic end with newline
    outf << "\n";

    return 0;
  }
};

#endif
