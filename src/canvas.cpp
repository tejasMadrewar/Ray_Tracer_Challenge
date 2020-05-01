#include "./canvas.h"

canvas::canvas() {
  Width = 0;
  Height = 0;
}

canvas::canvas(const canvas &can) {
  Width = can.Width;
  Height = can.Height;
  arr.resize(Width * Height, color());
  arr = can.arr;
}

canvas::canvas(int W, int H) {
  Width = W;
  Height = H;
  arr.resize(Width * Height, color());
}

color canvas::pixel_at(const int w, const int h) const {
  if (w >= Width || h >= Height || w < 0 || h < 0) {
    return color(0, 0, 0);
  }
  return arr.at((h * Width) + w);
}

void canvas::write_pixel(const int w, const int h, const color col) {
#if DEBUG_canvas
  std::cout << "writing_pixel: (" << w << "," << h << ")"
            << "\n";
#endif
  if (w >= Width || h >= Height || w < 0 || h < 0) {
    return;
  }
  arr.at((h * Width) + w) = col;
}

int canvas::canvas_to_ppm(std::string filename, int max) {

#if DEBUG_canvas_1
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
#if DEBUG_canvas
  std::cout << "canvas_to_ppm:\n";
#endif
  for (int i = 0; i < Height; i++) {
    for (int j = 0; j < Width; j++) {
      outf << fix_range(arr.at((i * Width) + j).red()) << " "
           << fix_range(arr.at((i * Width) + j).green()) << " "
           << fix_range(arr.at((i * Width) + j).blue()) << " ";

#if DEBUG_canvas
      std::cout << "(" << j << "," << i << ")"
                << " color:(";
      arr.at((i * Width) + j).print();
      std::cout << ")\n";

#endif

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
