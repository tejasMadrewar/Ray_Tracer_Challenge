#include "./world.h"
#include <memory>

void world::add_shape(std::shared_ptr<shape> sPtr) {
  this->vecShapes.push_back(sPtr);
}

void world::add_sphere(const mat &trans, const material &m) {
  std::shared_ptr<shape> s(new sphere());
  s->setMaterial(m);
  s->setTransform(trans);
  this->vecShapes.push_back(s);
}

void world::add_sphere(const mat &trans) {
  std::shared_ptr<shape> s(new sphere());
  s->setTransform(trans);
  this->vecShapes.push_back(s);
}

void world::add_plane(const mat &trans, const material &m) {
  std::shared_ptr<shape> s(new plane());
  s->setMaterial(m);
  s->setTransform(trans);
  this->vecShapes.push_back(s);
}

std::vector<intersection> world::intersect_world(ray &r) {
  // return vector of intersection
  // intersection contains shape* and intersected

  std::vector<intersection> worldIntersects;
  std::vector<intersection> temp;

  // for (auto &i : sVec) {
  for (auto &i : vecShapes) {
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

color world::shadeHit(preComputed p, int remaining) {
  color result, reflected, surface;
  bool Shadowed = this->isShadowed(p.overPoint);
  surface = lightening(p.objptr->getMaterial(), *(p.objptr), worldLight,
                       p.overPoint, p.eyev, p.normalv, Shadowed);

  reflected = this->reflectedColorAt(p, remaining);

  result = surface + reflected;

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

color world::colorAt(ray r, int remaining) {
  std::vector<intersection> iArray = intersect_world(r);
  intersection i = hit(iArray);
  if (i.obj == nullptr) { // ray does not hit shape
    return color(0, 0, 0);
  }
  preComputed p;
  p = prepareComputation(i, r);
  bool Shadowed = this->isShadowed(p.overPoint);

  return shadeHit(p, remaining);
}

bool world::isShadowed(point &p) {
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

color world::reflectedColorAt(preComputed p, int remaining) {
  color result(0, 0, 0);
  if (p.objptr->m.reflective == 0 || remaining == 0)
    return result;

  ray reflectedRay(p.overPoint, p.reflectv);
  color c = colorAt(reflectedRay, remaining - 1);
  result = c * p.objptr->m.reflective;

  return result;
}
