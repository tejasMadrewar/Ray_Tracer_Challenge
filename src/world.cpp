#include "./world.h"

void world::add_sphere(const mat &trans, const material &m) {
  shape *s1 = new sphere();
  s1->setMaterial(m);
  s1->setTransform(trans);
  this->sVec.push_back(s1);
}

void world::add_plane(const mat &trans, const material &m) {
  shape *s1 = new plane();
  s1->setMaterial(m);
  s1->setTransform(trans);
  this->sVec.push_back(s1);
}

void world::add_sphere(const mat &trans) {
  sphere *s1 = new sphere();
  s1->setTransform(trans);
  this->sVec.push_back(s1);
}

std::vector<intersection> world::intersect_world(ray &r) {

  std::vector<intersection> worldIntersects;
  std::vector<intersection> temp;

  for (auto &i : sVec) {
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

color world::shadeHit(preComputed p) {
  color result;
  bool Shadowed = this->isShadowed(p.overPoint);
  result = lightening(p.objptr->getMaterial(), worldLight, p.overPoint, p.eyev,
                      p.normalv, Shadowed);

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

color world::colorAt(ray r) {
  std::vector<intersection> iArray = intersect_world(r);
  intersection i = hit(iArray);
  if (i.obj == nullptr) { // ray does not hit shape
    return color(0, 0, 0);
  }
  preComputed p;
  p = prepareComputation(i, r);
  bool Shadowed = this->isShadowed(p.overPoint);
  return lightening(p.objptr->getMaterial(), worldLight, p.overPoint, p.eyev,
                    p.normalv, Shadowed);
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
