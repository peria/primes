#include "eratosthenes4.h"

#include <cmath>

namespace {

#include "constants.h"

}  // namespace

void Eratosthenes4::generate(int64 x) {
  flags_.clear();
  num_primes_ = 0;

  generateSmall(std::ceil(std::sqrt(x)));

  for (int64 size = x / 30 + (x % 30 != 0), offset = 0; size > 0;
       offset += kSegmentSize, size -= kSegmentSize) {
    initFlags(x, offset, size);
    generateCore(offset);
  }
}

void Eratosthenes4::initFlags(const int64 x, const int64 offset, const int64 size) {
  if (flags_.empty()) {
    flags_.resize(kSegmentSize, 0xff);
  } else {
    fill(flags_.begin(), flags_.end(), 0xff);
  }

  if (offset == 0) {
    flags_[0] = 0xfe;
  }
  if (size < static_cast<int64>(kSegmentSize)) {
    flags_.resize(size);
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
}

void Eratosthenes4::generateSmall(const int64 sqrt_x) {
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
      int64 ibit = BitToIndex(lsb);
      const int64 m = kMod30[ibit];
      int64 pm = 30 * i + 2 * m;
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

void Eratosthenes4::generateCore(const int64 /*offset*/) {
  const uint64 size = flags_.size();
  int32 p_index = 0;
  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 primes = sflags_[i]; primes; primes &= primes - 1) {
      uint8 lsb = primes & (-primes);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      uint64 index = indecies_[p_index];
      uint64 j = (index >> 3) - kSegmentSize;
      uint64 k = index & 7;
      while (j < size) {
        flags_[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }
      indecies_[p_index] = (j << 3) | k;
      ++p_index;
    }
  }

  for (uint64 i = 0; i < size / 8; ++i) {
    num_primes_ += PopCnt(*reinterpret_cast<uint64*>(flags_.data() + i * 8));
  }
  for (uint64 i = size / 8 * 8; i < size; ++i) {
    num_primes_ += PopCnt(flags_[i]);
  }
}

int64 Eratosthenes4::count() {
  return num_primes_ + 3;
}
