#ifndef MATERIAL_H
#define MATERIAL_H
#include "./color.h"
#include "./light.h"

#define MATERIAL_DEBUG 0

class material {

public:
  material() {}
  material(const material &n) {
    ambient = n.ambient;
    diffuse = n.diffuse;
    specular = n.specular;
    shiniess = n.shiniess;
    col = n.col;
  }

  bool operator==(const material &n) {
    return (ambient == n.ambient && diffuse == n.diffuse &&
            specular == n.specular && shiniess == n.shiniess);
  }

  // color
  color col = color(1, 1, 1);
  // 0-1 value
  float ambient = 0.1;
  float diffuse = 0.9;
  float specular = 0.9;

  // 10 very large highlight and d200 very small highlight
  float shiniess = 200;
};

namespace {
color lightening(material m, pointLight l, point position, vec eyev,
                 vec normalv, bool in_shadow = false) {
  color ambient, diffuse, specular, effective_color, result;
  vec lightv, reflectv;
  float light_dot_normal, reflect_dot_eye, factor;

  // combine the surface color with the light's colot/intensity
  effective_color = l.intensity * m.col;

  // find the direction to the light source
  lightv = (l.position - position).norm();

  // compute the ambient contribution
  ambient = effective_color * m.ambient;

  // condition point is in shadow
  if (in_shadow) {
    return ambient;
  }

  // light_dot_normal represents the cosine fo the angle between the light
  // vector and the normal vector. A negative number means the light is on the
  // other side of the surface
  light_dot_normal = dot(lightv, normalv);

  if (light_dot_normal < 0) {
    diffuse = color(0, 0, 0);  // black
    specular = color(0, 0, 0); // black
  } else {
    // diffuse computation
    diffuse = effective_color * m.diffuse * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the reflection
    // vector and the eye vector. A negative number means the light reflects
    // away form the eye.
    reflectv = (-lightv).reflect(normalv);
    reflect_dot_eye = dot(reflectv, eyev);

    if (reflect_dot_eye <= 0) {
      specular = color(0, 0, 0);
    } else {
      // compute specular contribution
      factor = pow(reflect_dot_eye, m.shiniess);
      specular = l.intensity * m.specular * factor;
    }
  }

#if MATERIAL_DEBUG
  std::cout << "\n-------------------\n"
            << "material lightening\n"
            << "-------------------"
            << "\nambient :";
  ambient.print();
  std::cout << "\ndiffuse :";
  diffuse.print();
  std::cout << "\nspecular :";
  specular.print();
  std::cout << "\n";
#endif

  result = ambient + diffuse + specular;

  return result;
}
} // namespace

#endif
