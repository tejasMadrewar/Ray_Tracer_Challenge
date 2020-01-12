#include "../canvas.h"
#include "../mat.h"
#include "../point.h"
#include "../transform.h"

#define DEBUG 0

int main() {
  const int height = 550;
  const int width = 900;
  canvas c(width, height);

  const float radius = height / 2 - 5;
  float radian = 0;

  transform t;
  point p(0, radius, 0);
  point result;
  const color col(255, 255, 255);

  for (int i = 1; i <= 12; ++i) {
    // rotate
    result = t.rotZ(2 * PI / 12 * i) * p;
    // translate
    result = t.translate(width / 2, height / 2, 0) * result;
    // draw point
    c.write_pixel(result.getX(), c.height() - result.getY(), col);

#if DEBUG
    std::cout << i << "-> radian: " << (2 * PI / 12 * i) << " point(";
    result.print();
    std::cout << ")\n";
#endif
  }

  //    int num = 10;
  //    int sector = 30;
  //    for (int j = 1; j < num; ++j) {
  //      //p = point(0, radius / num * j, 0);
  //      p.setY( radius / num * j);
  //      for (int i = 1; i <= sector; ++i) {
  //        radian = (2 * PI / sector) * i;
  //        result = t.rotZ(radian) * p;
  //        result = t.translate(900 / 2, 550 / 2, 0) * result;
  //        c.write_pixel(result.getX(), c.height() - result.getY(), col);
  //      }
  //    }

  c.canvas_to_ppm("clock.ppm");

  return 0;
}
