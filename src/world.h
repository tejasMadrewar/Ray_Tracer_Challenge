#ifndef WORLD_H
#define WORLD_H

#include "mat.h"
#define WORLD_DEBUG 0

#include "./light.h"
#include "./material.h"
#include "./object.h"
#include "./sphere.h"
#include "./transform.h"
#include <algorithm>

class world {
public:
  world() {}

  static world default_world() {
    world w;
    material m;
    transform t;

    w.worldLight.intensity = color(1, 1, 1);
    w.worldLight.position = point(-10, 10, -10);

    m.col = color(0.8, 1.0, 0.6);
    m.diffuse = 0.7;
    m.specular = 0.2;

    w.add_sphere(mat::Identity(4), m);
    w.add_sphere(t.scale(0.5, 0.5, 0.5));

    return w;
  }

  void add_sphere(const mat &trans, const material &m) {
    sphere *s1 = new sphere();
    s1->setMaterial(m);
    s1->setTransform(trans);
    this->sVec.push_back(s1);
  }

  void add_sphere(const mat &trans) {
    sphere *s1 = new sphere();
    s1->setTransform(trans);
    this->sVec.push_back(s1);
  }

  ~world() {
    for (auto i : sVec) {
      delete i;
    }
  }

  std::vector<intersection> intersect_world(ray r) {

    std::vector<intersection> worldIntersects;
    std::vector<intersection> temp;

    for (auto i : sVec) {
      temp = (*i).intersect(r);
      if (temp.size() != 0) {
        worldIntersects.insert(worldIntersects.end(), temp.begin(), temp.end());
      }
    }

    // sort before return
    std::sort(worldIntersects.begin(), worldIntersects.end());

#if WORLD_DEBUG
    std::cout << "----------------\n"
              << "intersect_world \n"
              << "----------------\n";
    for (auto i : worldIntersects) {
      std::cout << i.intersected << "\n";
    }
#endif

    return worldIntersects;
  }

  color shadeHit(preComputed p) {
    color result;
    bool Shadowed = this->isShadowed(p.overPoint);
    result = lightening(p.objptr->getMaterial(), worldLight, p.overPoint,
                        p.eyev, p.normalv, Shadowed);

#if WORLD_DEBUG
    std::cout << "----------------\n"
              << "shadeHit \n"
              << "----------------";
    std::cout << "\nobjptr :" << p.objptr;

    std::cout << "\nMATERIAL color:";
    p.objptr->getMaterial().col.print();
    std::cout << "\nMATERIAL ambient : " << p.objptr->getMaterial().ambient
              << "\nMATERIAL diffuse : " << p.objptr->getMaterial().diffuse
              << "\nMATERIAL shiniess: " << p.objptr->getMaterial().shiniess
              << "\nMATERIAL specular: " << p.objptr->getMaterial().specular;

    std::cout << "\nWORLDlIGHT i)POSITION:";
    worldLight.position.print();
    std::cout << " ii)INTENSITY:";
    worldLight.intensity.print();

    std::cout << "\nPOSITION ";
    p.position.print();

    std::cout << "\nEYEV ";
    p.position.print();

    std::cout << "\nNORMALV ";
    p.normalv.print();
    std::cout << "\nRESULT ";
    result.print();
    std::cout << "\n----------------\n\n";
#endif
    return result;
  }

  color colorAt(ray r) {
    std::vector<intersection> iArray = intersect_world(r);
    intersection i = hit(iArray);
    if (i.obj == nullptr) { // ray does not hit object
      return color(0, 0, 0);
    }
    preComputed p;
    p = prepareComputation(i, r);
    bool Shadowed = this->isShadowed(p.overPoint);
    return lightening(p.objptr->getMaterial(), worldLight, p.overPoint, p.eyev,
                      p.normalv, Shadowed);
  }

  bool isShadowed(point &p) {
    bool result = false;

    vec v = worldLight.position - p;
    float distance = v.mag();
    vec direction = v.norm();

    ray r(p, direction);
    std::vector<intersection> Is = this->intersect_world(r);
    intersection i = hit(Is);
    if (i.obj != nullptr && i.intersected < distance) {
      result = true;
    }
    return result;
  }

public:
  pointLight worldLight;

  std::vector<object *> sVec;

private:
  material m;
  transform t;
};

#endif
