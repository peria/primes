#include "generator0.h"

#include <cmath>

PrimeGenerator0::PrimeGenerator0(int64 x)
    : x_(x), flags_(x, true) { }

void PrimeGenerator0::sieve() {
  flags_[0] = false;
  flags_[1] = false;

  const int64 sqrt_x = std::ceil(std::sqrt(x_) + 0.5);
  for (int64 p = 2; p < sqrt_x; ++p) {
    if (!flags_[p])
      continue;
    for (int64 mult = p * p; mult < x_; mult += p)
      flags_[mult] = false;
  }
}

int64 PrimeGenerator0::count() {
  int64 ret = 0;
  for (bool f : flags_) {
    if (f)
      ++ret;
  }
  return ret;
}
