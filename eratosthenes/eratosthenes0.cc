#include "eratosthenes0.h"

#include <cmath>

void Eratosthenes0::generate(int64 x) {
  flags_.clear();
  if (x > 100000000)
    return;

  flags_.resize(x, true);

  flags_[0] = false;
  flags_[1] = false;
  const int64 sqrt_x = std::ceil(std::sqrt(x) + 0.1);
  for (int64 p = 2; p < sqrt_x; ++p) {
    if (!flags_[p])
      continue;
    for (int64 mult = p * p; mult < x; mult += p)
      flags_[mult] = false;
  }
}

int64 Eratosthenes0::count() {
  if (flags_.empty())
    return -1;

  int64 ret = 0;
  for (bool f : flags_) {
    if (f)
      ++ret;
  }
  return ret;
}
