#include "./sphere.h"

sphere::sphere(point ori, float r) {
  xsSecond.resize(2, intersection(this));
  origin = ori;
  radius = r;
}

void sphere::print() {
  std::cout << "---------------\n";
  std::cout << "sphere\n";
  std::cout << "---------------\n";
  std::cout << "transform\n";
  Transform.print();
  std::cout << "---------------\n";
}

// find local intersection
std::vector<intersection> sphere::local_intersect(ray &r) {
  // save the ray into class variables
  saved_ray = r;

  std::vector<intersection> xs;
  float a, b, c, discirminant;
  vec sphere_to_ray = r.origin - point(0, 0, 0);

  a = dot(r.direction, r.direction);
  b = 2 * dot(r.direction, sphere_to_ray);
  c = dot(sphere_to_ray, sphere_to_ray) - 1;

  discirminant = (b * b) - (4 * a * c);

#if DEBUG_SPHERE
  std::cout << "\nDEBUG_SPHERE";
  std::cout << "\nr.direction ";
  r.direction.print();
  std::cout << "\nr.origin ";
  r.origin.print();
  std::cout << "\nsphere_to_ray ";
  sphere_to_ray.print();
  std::cout << "\na:" << a << " b:" << b << " c:" << c;
  std::cout << "\ndiscirminant " << discirminant;
#endif

  // ray is not hitting the sphere
  if (discirminant < 0) {
    return xs;
  }

  // xs.resize(2, intersection(this)); // replace this with xsSecond to avoid
  // allocation each time intersected is invoked
  xsSecond[0].intersected = (-b - sqrt(discirminant)) / (2 * a);
  xsSecond[1].intersected = (-b + sqrt(discirminant)) / (2 * a);

  // sort
  if (xsSecond[0].intersected > xsSecond[1].intersected) {
    std::swap(xsSecond[0].intersected, xsSecond[1].intersected);
  }

#if DEBUG_SPHERE
  std::cout << "\nxs[0] " << xsSecond[0].intersection;
  std::cout << "\nxs[1] " << xsSecond[1].intersection;
#endif
  return xsSecond;
}

// get normal at point assume point is on sphere
vec sphere::localNormalAt(point &objPoint) {
  vec normal = objPoint - origin;
  return normal.norm(); // always return normalize vector
}
