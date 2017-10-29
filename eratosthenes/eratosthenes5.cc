#include "eratosthenes5.h"

#include <cmath>

namespace {
#include "constants.h"
}  // namespace

void Eratosthenes5::initialize() {
  initial_.resize(kInitialSize + kSegmentSize);

  int64 size = 1;
  initial_[0] = 0xff;
  auto head = initial_.begin();
  for (int64 ibit : {1, 2, 3, 4, 5, 6}) {
    const int64 p = kMod30[ibit];
    for (int64 i = 1; i < p; ++i) {
      copy(head, head + size, head + size * i);
    }
    size *= p;
    for (int64 j = 0, k = 0; j < size;) {
      initial_[j] &= kMask[ibit][k];
      j += C0[ibit][k];
      k = (k + 1) & 7;
    }
  }
  copy(head, head + kSegmentSize, head + kInitialSize);
}

void Eratosthenes5::generate(const int64 x) {
  generate(0, x);
}

void Eratosthenes5::generate(const int64 from, const int64 to) {
  flags_.clear();
  num_primes_ = 0;
  for (int64 p : kSievedPrimes) {
    if (from <= p && p < to)
      ++num_primes_;
  }

  const int64 from_byte = from / 30;
  const int64 to_byte = to / 30 + (to % 30 != 0);
  generateSmall(from_byte, std::ceil(std::sqrt(to)));
  int64 from_rem = from % 30;
  for (int64 size = to_byte - from_byte, offset = from_byte; size > 0;
       offset += kSegmentSize, size -= kSegmentSize) {
    initFlags(from_rem, to, offset, size);
    generateCore(offset);
  }
}

void Eratosthenes5::initFlags(const int64 from_rem, const int64 to,
                              const int64 offset, const int64 size) {
  if (flags_.empty()) {
    flags_.resize(kSegmentSize);
    auto head = initial_.begin() + offset % kInitialSize;
    copy(head, head + flags_.size(), flags_.begin());
    if (from_rem) {
      if (from_rem < 7)       flags_[0] &= 0xfe;
      else if (from_rem < 11) flags_[0] &= 0xfc;
      else if (from_rem < 13) flags_[0] &= 0xf8;
      else if (from_rem < 17) flags_[0] &= 0xf0;
      else if (from_rem < 19) flags_[0] &= 0xe0;
      else if (from_rem < 23) flags_[0] &= 0xc0;
      else if (from_rem < 29) flags_[0] &= 0x80;
    }
  } else {
    auto head = initial_.begin() + offset % kInitialSize;
    copy(head, head + flags_.size(), flags_.begin());
  }

  if (offset == 0) {
    flags_[0] &= 0xfe;
  }
  if (size < static_cast<int64>(kSegmentSize)) {
    flags_.resize(size);
    if (int64 r = to % 30) {
      if (r <= 1)       flags_[size - 1] &= 0x0;
      else if (r <= 7)  flags_[size - 1] &= 0x1;
      else if (r <= 11) flags_[size - 1] &= 0x3;
      else if (r <= 13) flags_[size - 1] &= 0x7;
      else if (r <= 17) flags_[size - 1] &= 0xf;
      else if (r <= 19) flags_[size - 1] &= 0x1f;
      else if (r <= 23) flags_[size - 1] &= 0x3f;
      else if (r <= 29) flags_[size - 1] &= 0x7f;
    }
  }
}

void Eratosthenes5::generateSmall(const uint64 offset, const int64 sqrt_to) {
  sflags_.clear();
  indecies_.clear();

  const uint64 isqrt_to = sqrt_to / 30 + 1;
  const int64 quart_to = std::ceil(std::sqrt(sqrt_to));
  const uint64 iquart_to = quart_to / 30 + 1;

  sflags_.resize(isqrt_to, 0xff);
  sflags_[0] = 0xfe;
  for (uint64 i = 0; i < iquart_to; ++i) {
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

  sflags_[0] &= 0x80;
  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 flags = sflags_[i]; flags; flags &= flags - 1) {
      uint8 lsb = flags & (-flags);
      int64 ibit = BitToIndex(lsb);
      const int64 m = kMod30[ibit];
      uint64 j = i * (30 * i + 2 * m) + (m * m) / 30;
      int64 jbit = ibit;
      if (j < offset) {
        int64 p = 30 * i + m;
        j = (offset - i) / p * p + i;
        jbit = 0;
        while (j < offset) {
          j += i * C1[jbit] + C0[ibit][jbit];
          jbit = (jbit + 1) & 7;
        }
      }
      indecies_.push_back(((j - offset) << 3) | jbit);
    }
  }
}

void Eratosthenes5::generateCore(const int64 /*offset*/) {
  const uint64 size = flags_.size();
  auto itr = indecies_.begin();
  for (uint64 i = 0; i < sflags_.size(); ++i) {
    for (uint8 primes = sflags_[i]; primes; primes &= primes - 1) {
      uint8 lsb = primes & (-primes);
      int ibit = BitToIndex(lsb);
      uint64 index = *itr;
      uint64 j = index >> 3;
      uint64 k = index & 7;
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

int64 Eratosthenes5::count() {
  return num_primes_;
}
