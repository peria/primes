#pragma once

#include <cassert>
#include "base.h"

class Eratosthenes {
 public:
  // Set up common tasks independent from input values.
  virtual void initialize() {}

  // Find prime numbers in range [0, x).
  virtual void generate(const int64 x) = 0;

  // Find prime numbers in range [from, to).
  virtual void generate(const int64 from, const int64 to) {
    assert (from == 0);
    generate(to);
  }

  // Returns the number of counted prime numbers.
  virtual int64 count() = 0;

  // Returns the implemented version.
  virtual int32 version() = 0;

  inline uint64 PopCnt(uint64);
  inline int BitToIndex(uint8);
};

#include "eratosthenes_inline.h"
