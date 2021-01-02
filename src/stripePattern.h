#ifndef STRIPE_PATTERN_H
#define STRIPE_PATTERN_H

#include "pattern.h"
// ------------------------------------------------------------------
// stripe pattern class
// ------------------------------------------------------------------
//
#if 0
class stripePattern : public pattern {
public:
  stripePattern(color m, color n) {
    a = m;
    b = n;
  }
  ~stripePattern() {}

  color stripeAt(point &p) {
    // % operator is only for short, int, long, long long
    if ((int)floor(p.getX()) % 2 == 0) // compare for x coordinate
      return a;
    else
      return b;
  }
};
#endif
// ------------------------------------------------------------------

#endif
