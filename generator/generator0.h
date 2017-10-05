#pragma once

#include <vector>
#include "base.h"
#include "generator_base.h"

// Generate prime numbers up to x.
class PrimeGenerator0 final : public PrimeGeneratorBase {
 public:
  PrimeGenerator0(int64 x);
  void sieve() override;
  int64 count() override;

 private:
  const int64 x_;
  std::vector<bool> flags_;
};
