#include "generator1.h"

#include <cmath>

PrimeGenerator1::PrimeGenerator1(int64 x)
    : x_(x), flags_(x / 2, true) { }

void PrimeGenerator1::sieve() {
  flags_[0] = false;

  const int64 sqrt_x = std::ceil(std::sqrt(x_) + 0.5);
  const int64 sqrt_xi = sqrt_x / 2;
  const int64 xi = flags_.size();
  for (int64 i = 1; i < sqrt_xi; ++i) {
    if (!flags_[i])
      continue;
    const int64 p = 2 * i + 1;
    for (int64 mult = 2 * i * (i + 1); mult < xi; mult += p)
      flags_[mult] = false;
  }
}

int64 PrimeGenerator1::count() {
  int64 ret = 1;  // count '2'
  for (bool f : flags_) {
    if (f)
      ++ret;
  }
  return ret;
}
