#pragma once

#include "base.h"

class PrimeGeneratorBase {
 public:
  virtual void generate(int64 x) = 0;
  virtual int64 count() = 0;
  virtual int32 version() = 0;
};
