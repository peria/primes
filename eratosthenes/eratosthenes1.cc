#include "eratosthenes1.h"

#include <cmath>

void Eratosthenes1::generate(int64 x) {
  flags_.clear();
  if (x > 1000000000)
    return;

  flags_.resize(x / 2, true);

  flags_[0] = false;
  const uint64 sqrt_x = std::ceil(std::sqrt(x) + 0.1);
  const uint64 sqrt_xi = sqrt_x / 2;
  for (uint64 i = 1; i < sqrt_xi; ++i) {
    if (!flags_[i])
      continue;
    const uint64 p = 2 * i + 1;
    for (uint64 mult = 2 * i * (i + 1); mult < flags_.size(); mult += p)
      flags_[mult] = false;
  }
}

int64 Eratosthenes1::count() {
  if (flags_.empty())
    return -1;

  int64 ret = 1;  // count '2'
  for (bool f : flags_) {
    if (f)
      ++ret;
  }
  return ret;
}
