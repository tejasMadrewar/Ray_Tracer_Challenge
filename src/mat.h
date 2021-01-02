#ifndef MAT_H
#define MAT_H

#include "./tuple.h"
#include <iostream>
#include <vector>

#define DEBUG_mat 0

class mat {
public:
  mat(int r, int c);
  mat(int size);
  mat(const mat &Mat);
  void from_vec(const std::vector<float> &ar);
  void print();
  float &at(int r, int c) { return values.at(r * Col + c); }
  const float at(int r, int c) const { return values.at(r * Col + c); }
  int row() { return Row; }
  int col() { return Col; }

  // operator overload
  bool operator==(const mat &Mat);
  bool operator!=(const mat &Mat);
  mat operator*(const mat &Mat);
  // mat MULTIPICATION with tuple
  tuple operator*(tuple &Tup);

  // matrix operation
  static mat Identity(int size); // make Identity matrix of given size
  mat transpose();               // make transpose matrix of given size
  float det();
  mat subMat(int r1, int c1);
  float minor(int r1, int c1) { return subMat(r1, c1).det(); }
  float cofactor(int r1, int c1);
  bool invertable() { return det() != 0; }
  mat inverse();

private:
  int Row = 0, Col = 0;
  std::vector<float> values;
};

#endif
