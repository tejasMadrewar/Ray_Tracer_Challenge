#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

#include "./mat.h"
#include "./point.h"
#include "./transform.h"
#include "./vec.h"

class transformation {
public:
  transformation() {}
  mat view_transform(point &from, point &to, vec &up) {
    mat result(4), orientation(4);
    vec forward = (to - from).norm();
    vec upn = up.norm();
    vec left = cross(forward, upn);
    vec true_up = cross(left, forward);
    transform t;

    orientation.at(0, 0) = left.getX();
    orientation.at(0, 1) = left.getY();
    orientation.at(0, 2) = left.getZ();
    orientation.at(0, 3) = 0;

    orientation.at(1, 0) = true_up.getX();
    orientation.at(1, 1) = true_up.getY();
    orientation.at(1, 2) = true_up.getZ();
    orientation.at(1, 3) = 0;

    orientation.at(2, 0) = -forward.getX();
    orientation.at(2, 1) = -forward.getY();
    orientation.at(2, 2) = -forward.getZ();
    orientation.at(2, 3) = 0;

    orientation.at(3, 0) = 0;
    orientation.at(3, 1) = 0;
    orientation.at(3, 2) = 0;
    orientation.at(3, 3) = 1;

    result =
        orientation * t.translate(-from.getX(), -from.getY(), -from.getZ());

    return result;
  }

private:
};

#endif
