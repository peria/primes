#pragma once

#include "base.h"

class PrimeGeneratorBase {
 public:
  virtual void sieve() = 0;
  virtual int64 count() = 0;
};
