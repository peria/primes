#include "eratosthenes6.h"

#include <cmath>

namespace {
#include "constants.h"
}  // namespace

void Eratosthenes6::generateCore(const int64 /*offset*/) {
  const uint64 size = flags_.size();
  auto itr = indecies_.begin();
  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 primes = sflags_[i]; primes; primes &= primes - 1) {
      const uint8 lsb = primes & (-primes);
      const int ibit = BitToIndex(lsb);
      const uint64 index = *itr;
      uint64 j = index >> 3;
      uint64 k = index & 7;

      while (k && j < size) {
        flags_[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }

      while (j + i * 28 + kMod30[ibit] - 1 < size) {
        flags_[j] &= kMask[ibit][0]; j += i * C1[0] + C0[ibit][0];
        flags_[j] &= kMask[ibit][1]; j += i * C1[1] + C0[ibit][1];
        flags_[j] &= kMask[ibit][2]; j += i * C1[2] + C0[ibit][2];
        flags_[j] &= kMask[ibit][3]; j += i * C1[3] + C0[ibit][3];
        flags_[j] &= kMask[ibit][4]; j += i * C1[4] + C0[ibit][4];
        flags_[j] &= kMask[ibit][5]; j += i * C1[5] + C0[ibit][5];
        flags_[j] &= kMask[ibit][6]; j += i * C1[6] + C0[ibit][6];
        flags_[j] &= kMask[ibit][7]; j += i * C1[7] + C0[ibit][7];
      }

      while (j < size) {
        flags_[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }

      *itr = ((j - kSegmentSize) << 3) | k;
      ++itr;
    }
  }

  for (uint64 i = 0; i < size / 8; ++i) {
    num_primes_ += PopCnt(*reinterpret_cast<uint64*>(flags_.data() + i * 8));
  }
  for (uint64 i = size / 8 * 8; i < size; ++i) {
    num_primes_ += PopCnt(flags_[i]);
  }
}
