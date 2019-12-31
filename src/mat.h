#ifndef MAT_H
#define MAT_H

#include "./tuple.h"
#include <iostream>
#include <vector>

#define DEBUG_mat 0

class mat {
public:
  mat(int r, int c) {
    Row = r;
    Col = c;
    values.resize(r * c, 0.0);
  }

  mat(int size) {
    Row = size;
    Col = size;
    values.resize(size * size, 0.0);
  }

  mat(const mat &Mat) {
    Row = Mat.Row;
    Col = Mat.Col;
    values = Mat.values;
  }

  void from_vec(const std::vector<float> &ar) {
    if (ar.size() < (Row * Col))
      throw;
    for (int r = 0; r < Row; r++) {
      for (int c = 0; c < Col; c++) {
        at(r, c) = ar.at(r * Col + c);
      }
    }
  }

  void print() {
    for (int r = 0; r < Row; r++) {
      for (int c = 0; c < Col; c++) {
        std::cout << "|" << at(r, c) << " ";
      }
      std::cout << "|\n";
    }
  }

  bool operator==(const mat &Mat) {
    // return (Row == Mat.Row && Col == Mat.Col && values == Mat.values);
    const float EPSILON = 0.0001;
    if (Row == Mat.Row && Col == Mat.Col &&
        values.size() == Mat.values.size()) {
      for (int i = 0; i < values.size(); i++) {
        if (fabs(values.at(i) - Mat.values.at(i)) > EPSILON)
          return false;
      }
    } else {
      return false;
    }
    return true;
  }

  bool operator!=(const mat &Mat) {
    // return !(Row == Mat.Row && Col == Mat.Col && values == Mat.values);
    const float EPSILON = 0.0001;
    if (Row == Mat.Row && Col == Mat.Col &&
        values.size() == Mat.values.size()) {
      for (int i = 0; i < values.size(); i++) {
        if (fabs(values.at(i) - Mat.values.at(i)) > EPSILON)
          return true;
      }
    } else {
      return true;
    }
    return false;
  }

  float &at(int r, int c) { return values.at(r * Col + c); }
  const float at(int r, int c) const { return values.at(r * Col + c); }

  int row() { return Row; }

  int col() { return Col; }

  mat operator*(const mat &Mat) {
    if (Col != Mat.Row) // MULTIPICATION not possible
      throw;

#if DEBUG_mat
    std::cout << "MATRIX MULTIPICATION with Matrix\n";
#endif

    mat ans = mat(Row, Mat.Col);
    float temp = 0.0;
    for (int r = 0; r < ans.Row; r++) {
      for (int c = 0; c < ans.Col; c++) {
        for (int z = 0; z < ans.Col; z++) {

#if DEBUG_mat
          std::cout << at(r, z) << "*" << Mat.at(z, c) << " ";
#endif

          temp = temp + at(r, z) * Mat.at(z, c);
          // temp = temp + at(1,z) * Mat.at(z,0);
          // temp = temp + at(1,1) * Mat.at(1,0);
          // temp = temp + at(1,2) * Mat.at(2,0);
          // temp = temp + at(1,3) * Mat.at(4,0);
        }

#if DEBUG_mat
        std::cout << "\n";
#endif

        ans.at(r, c) = temp;
        temp = 0;
      }
    }

    return ans;
  }

  // mat MULTIPICATION with tuple
  tuple operator*(tuple &Tup) {
    if (Col != 4) // MULTIPICATION not possible
      throw;

#if DEBUG_mat
    std::cout << "MATRIX MULTIPICATION with tuple\n";
#endif

    tuple ans;
    float temp = 0.0;
    for (int r = 0; r < Col; r++) {
      for (int z = 0; z < Col; z++) {

#if DEBUG_mat
        std::cout << at(r, z) << "*" << Tup.t[z] << " ";
#endif

        temp = temp + at(r, z) * Tup.t[z];
        // temp = temp + at(1,0) * Tup.t[0];
        // temp = temp + at(1,1) * Tup.t[1];
        // temp = temp + at(1,2) * Tup.t[2];
        // temp = temp + at(1,3) * Tup.t[4];
      }

#if DEBUG_mat
      std::cout << "\n";
#endif

      ans.t[r] = temp;
      temp = 0;
    }

    return ans;
  }

  mat Identity(int size) { // make Identity matrix of given size
    mat result(size);
    result.Col = size;
    result.Row = size;
    for (int i = 0; i < result.Col; i++) {
      result.at(i, i) = 1;
    }

    return result;
  }

  mat transpose() { // make transpose matrix of given size
    mat result(Col, Row);

    for (int r = 0; r < Row; r++) {
      for (int c = 0; c < Col; c++) {
        // transpose
        result.at(c, r) = at(r, c);
      }
    }
    return result;
  }

  float det() {
    float result = 0;
    if (Row != Col)
      throw;
    if (Row == 2 && Col == 2) {
      result = (at(0, 0) * at(1, 1)) - (at(0, 1) * at(1, 0));
    } else {
      float temp = 0;
      for (int i = 0; i < Col; i++) {
        result = result + (at(0, i) * cofactor(0, i));
      }
    }

    return result;
  }

  mat subMat(int r1, int c1) {
    mat result(Row - 1, Col - 1);
    int counter = 0;
    for (int r = 0; r < Row; r++) {
      for (int c = 0; c < Col; c++) {
        if (r == r1 || c == c1)
          continue;
        result.values.at(counter) = at(r, c);
        ++counter;
      }
    }

    return result;
  }

  float minor(int r1, int c1) { return subMat(r1, c1).det(); }

  float cofactor(int r1, int c1) {
    if ((r1 + c1) % 2 == 0)
      return subMat(r1, c1).det();
    else
      return -subMat(r1, c1).det();
  }

  bool invertable() { return det() != 0; }

  mat inverse() {
    mat result(Col);
    float Det = det();

    if (Row == Col && Det != 0) {

      for (int r = 0; r < Row; r++) {
        for (int c = 0; c < Col; c++) {
          result.at(r, c) = cofactor(c, r) / Det;
        }
      }
    } else
      throw;

    return result;
  }

private:
  int Row = 0, Col = 0;
  std::vector<float> values;
};

#endif
