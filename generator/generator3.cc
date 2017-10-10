#include "generator3.h"

#include <cmath>

#include <iostream>

namespace {

int BitToIndex(uint8 b) {
  switch (b) {
  case 1 << 0:  return 0;
  case 1 << 1:  return 1;
  case 1 << 2:  return 2;
  case 1 << 3:  return 3;
  case 1 << 4:  return 4;
  case 1 << 5:  return 5;
  case 1 << 6:  return 6;
  case 1 << 7:  return 7;
  }
  return -1;
}

const int32 kMod30[] = {1, 7, 11, 13, 17, 19, 23, 29};

// m = [1, 7, 11, 13, 17, 19, 23, 29]
// n = [   7, 11, 13, 17, 19, 23, 29, 31]

// [n0-m0 for (n0,m0) in zip(n, m)]
const int C1[] = {6, 4, 2, 4, 2, 4, 6, 2};

// [[m0*n1/30-m0*m1/30 for (n1,m1) in zip(n, m)] for m0 in m]
const int C0[][8] = {
  {0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 0, 1, 1, 1, 1},
  {2, 2, 0, 2, 0, 2, 2, 1}, {3, 1, 1, 2, 1, 1, 3, 1},
  {3, 3, 1, 2, 1, 3, 3, 1}, {4, 2, 2, 2, 2, 2, 4, 1},
  {5, 3, 1, 4, 1, 3, 5, 1}, {6, 4, 2, 4, 2, 4, 6, 1},
};

// [[bitoff(m0*m1%30) for m1 in m] for m0 in m]
const uint8 kMask[][8] = {
  {0xfe, 0xfd, 0xfb, 0xf7, 0xef, 0xdf, 0xbf, 0x7f},
  {0xfd, 0xdf, 0xef, 0xfe, 0x7f, 0xf7, 0xfb, 0xbf},
  {0xfb, 0xef, 0xfe, 0xbf, 0xfd, 0x7f, 0xf7, 0xdf},
  {0xf7, 0xfe, 0xbf, 0xdf, 0xfb, 0xfd, 0x7f, 0xef},
  {0xef, 0x7f, 0xfd, 0xfb, 0xdf, 0xbf, 0xfe, 0xf7},
  {0xdf, 0xf7, 0x7f, 0xfd, 0xbf, 0xfe, 0xef, 0xfb},
  {0xbf, 0xfb, 0xf7, 0x7f, 0xfe, 0xef, 0xdf, 0xfd},
  {0x7f, 0xbf, 0xdf, 0xef, 0xf7, 0xfb, 0xfd, 0xfe},
};

const uint64 kSegmentSize = 10000;  // 10kB

}  // namespace

void PrimeGenerator3::generate(int64 x) {
  flags_.clear();
  indecies_.clear();
  if (x > 1000000000)
    return;

  {
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
  }

  const uint64 segment_size = std::min(kSegmentSize, flags_.size());
  const uint64 sqrt_x = std::ceil(std::sqrt(x) + 0.1);
  const uint64 sqrt_xi = sqrt_x / 30 + 1;
  generateSmall(segment_size, sqrt_xi);

  int64 size = flags_.size() - kSegmentSize;
  for (uint8* segment = flags_.data() + kSegmentSize; size > 0;
       segment += kSegmentSize, size -= kSegmentSize) {
    generateCore(segment, std::min<uint64>(size, kSegmentSize), sqrt_xi);
  }
}

void PrimeGenerator3::generateSmall(const uint64 segment_size, uint64 sqrt_xi) {
  for (uint64 i = 0; i < sqrt_xi; ++i) {
    for (uint8 flags = flags_[i]; flags; flags &= flags - 1) {
      uint8 lsb = flags & (-flags);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      int32 pm = 30 * i + 2 * m;
      uint64 j = i * pm + (m * m) / 30;
      uint64 k = ibit;
      while (j < segment_size) {
        flags_[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }
      indecies_.push_back((j << 3) | k);
    }
  }
}

void PrimeGenerator3::generateCore(uint8* flags, const uint64 size, uint64 sqrt_xi) {
  int32 p_index = 0;
  for (uint64 i = 0; i < sqrt_xi; ++i) {
    for (uint8 primes = flags_[i]; primes; primes &= primes - 1) {
      uint8 lsb = primes & (-primes);
      int ibit = BitToIndex(lsb);
      const int32 m = kMod30[ibit];
      uint64 index = indecies_[p_index];
      uint64 j = (index >> 3) - kSegmentSize;
      uint64 k = index & 7;
      while (j < size) {
        flags[j] &= kMask[ibit][k];
        j += i * C1[k] + C0[ibit][k];
        k = (k + 1) & 7;
      }
      indecies_[p_index] = (j << 3) | k;
      ++p_index;
    }
  }
}

int64 PrimeGenerator3::count() {
  if (flags_.empty())
    return -1;

  int64 ret = 3;  // count 2, 3, 5
  for (uint8 f : flags_) {
    ret += PopCnt(f);
  }
  return ret;
}
