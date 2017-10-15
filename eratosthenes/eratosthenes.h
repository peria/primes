#pragma once

#include "base.h"

class Eratosthenes {
 public:
  virtual void generate(int64 x) = 0;
  virtual int64 count() = 0;
  virtual int32 version() = 0;

  inline uint64 PopCnt(uint64);
  inline int BitToIndex(uint8);
};

#include "eratosthenes_inline.h"
