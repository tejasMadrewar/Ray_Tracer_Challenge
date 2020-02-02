#ifndef CAMERA_H
#define CAMERA_H

#include "./canvas.h"
#include "./mat.h"
#include "./ray.h"
#include "./transformation.h"
#include "./world.h"
#include <cmath>

class camera {
public:
  camera(int thsize, int tvsize, float tfieldOfView) {
    hsize = thsize;
    vsize = tvsize;
    fieldOfView = tfieldOfView;

    // calculating pixelSize
    halfView = tan(fieldOfView / 2);
    aspect = hsize / vsize;

    if (aspect >= 1) {
      halfWidth = halfView;
      halfHeight = halfView / aspect;
    } else {
      halfWidth = halfView * aspect;
      halfHeight = halfView;
    }
    pixelSize = (halfWidth * 2) / hsize;
  }

  ray ray_for_pixel(int px, int py) {
    float xoffset, yoffset;
    float worldX, worldY;

    point pixel, origin;
    point tempOrigin(0, 0, 0);
    point tempPixel;
    vec direction;

    // offset from the dege of canvas to the pixels center
    xoffset = (px + 0.5) * pixelSize;
    yoffset = (py + 0.5) * pixelSize;

    // the untransformed coordinates of the pixel in the world space
    // (remember that the camera looks towards -z so +x is to the *left*
    worldX = halfWidth - xoffset;
    worldY = halfHeight - yoffset;

    // using camera matrix, transform the canvas point and the origin
    // and then compute the rays direction vector
    // (remember that the canvas is at z = -1)

    tempPixel = point(worldX, worldY, -1);

    pixel = transformInverse * tempPixel;
    origin = transformInverse * tempOrigin;
    direction = vec(pixel - origin).norm();

    return ray(origin, direction);
  }

  void setTransform(mat &trans) {
    transform = trans;
    transformInverse = transform.inverse();
  }

  mat getTransform() { return transform; }

  canvas render(world &w) {
    canvas image(hsize, vsize);
    ray r(point(0, 0, 0), vec(0, 0, 0));
    color col;

    for (int y = 0; y < vsize - 1; ++y) {
      for (int x = 0; x < hsize - 1; ++x) {
        r = ray_for_pixel(x, y);
        // col = w.colorAt(r);
        // image.write_pixel(x, y, col);
        image.write_pixel(x, y, w.colorAt(r));
      }
    }
    return image;
  }

  float hsize, vsize;
  float fieldOfView;
  float pixelSize;
  float halfView, aspect, halfWidth, halfHeight;

private:
  mat transform = mat::Identity(4);
  mat transformInverse = mat::Identity(4);
};

#endif
