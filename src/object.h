#ifndef OBJECT_H
#define OBJECT_H 1

namespace {

class object {
public:
  object() { id = counter++; }

  int getID() { return id; }

private:
  int id = 0;
  static int counter;
};

int object::counter = 0;
} // namespace
#endif
