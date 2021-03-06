#include "eratosthenes2.h"

#include <cmath>

namespace {
#include "constants.h"
}  // namespace

void Eratosthenes2::generate(const int64 x) {
  flags_.clear();
  if (x > 10000000000)
    return;

  int64 size = x / 30 + (x % 30 != 0);
  flags_.resize(size, 0xff);
  if (int r = x % 30) {
    if (r <= 1)       flags_[size - 1] = 0x0;
    else if (r <= 7)  flags_[size - 1] = 0x1;
    else if (r <= 11) flags_[size - 1] = 0x3;
    else if (r <= 13) flags_[size - 1] = 0x7;
    else if (r <= 17) flags_[size - 1] = 0xf;
    else if (r <= 19) flags_[size - 1] = 0x1f;
    else if (r <= 23) flags_[size - 1] = 0x3f;
    else if (r <= 29) flags_[size - 1] = 0x7f;
  }

  flags_[0] = 0xfe;
  const uint64 sqrt_x = std::ceil(std::sqrt(x) + 0.1);
  const uint64 sqrt_xi = sqrt_x / 30 + 1;
  for (uint64 i = 0; i < sqrt_xi; ++i) {
    for (uint8 flags = flags_[i]; flags; flags &= flags - 1) {
      uint8 lsb = flags & (-flags);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      int32 pm = 30 * i + 2 * m;
      for (uint64 j = i * pm + (m * m) / 30, k = ibit; j < flags_.size();
           j += i * C1[k] + C0[ibit][k], k = (k + 1) & 7) {
        flags_[j] &= kMask[ibit][k];
      }
    }
  }
}

int64 Eratosthenes2::count() {
  if (flags_.empty())
    return -1;

  int64 ret = 3;  // count 2, 3, 5
  for (uint8 f : flags_) {
    ret += PopCnt(f);
  }
  return ret;
}
