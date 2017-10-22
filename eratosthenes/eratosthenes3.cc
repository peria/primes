#include "eratosthenes3.h"

#include <cmath>

namespace {
#include "constants.h"
}  // namespace

void Eratosthenes3::generate(int64 x) {
  if (x > 10000000000)
    return;

  generateSmall(std::ceil(std::sqrt(x)));
  int64 size = x / 30 + (x % 30 != 0);
  initFlags(x, size);
  for (uint8* segment = flags_.data(); size > 0;
       segment += kSegmentSize, size -= kSegmentSize) {
    generateCore(segment, std::min<uint64>(size, kSegmentSize));
  }
}

void Eratosthenes3::initFlags(const int64 x, const int64 size) {
  flags_.clear();
  flags_.resize(size, 0xff);

  flags_[0] = 0xfe;
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
}

void Eratosthenes3::generateSmall(const int64 sqrt_x) {
  sflags_.clear();
  indecies_.clear();

  const uint64 sqrt_xi = sqrt_x / 30 + 1;
  const int64 quart_x = std::ceil(std::sqrt(sqrt_x));
  const uint64 quart_xi = quart_x / 30 + 1;

  sflags_.resize(sqrt_xi, 0xff);
  sflags_[0] = 0xfe;
  for (uint64 i = 0; i < quart_xi; ++i) {
    for (uint8 flags = sflags_[i]; flags; flags &= flags - 1) {
      uint8 lsb = flags & (-flags);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      int32 pm = 30 * i + 2 * m;
      uint64 j = i * pm + (m * m) / 30;
      uint64 k = ibit;
      while (j < sflags_.size()) {
        sflags_[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }
    }
  }

  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 flags = sflags_[i]; flags; flags &= flags - 1) {
      uint8 lsb = flags & (-flags);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      uint64 j = i * (30 * i + 2 * m) + (m * m) / 30;
      indecies_.push_back(((j + kSegmentSize) << 3) | ibit);
    }
  }
}

void Eratosthenes3::generateCore(uint8* flags, const uint64 size) {
  auto p_index = indecies_.begin();
  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 primes = sflags_[i]; primes; primes &= primes - 1) {
      uint8 lsb = primes & (-primes);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      uint64 index = *p_index;
      uint64 j = (index >> 3) - kSegmentSize;
      uint64 k = index & 7;
      while (j < size) {
        flags[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }
      *p_index = (j << 3) | k;
      ++p_index;
    }
  }
}

int64 Eratosthenes3::count() {
  if (flags_.empty())
    return -1;

  int64 ret = 3;  // count 2, 3, 5
  for (uint8 f : flags_) {
    ret += PopCnt(f);
  }
  return ret;
}
