#pragma once

#include <vector>
#include "base.h"
#include "generator_base.h"

// Generate prime numbers up to x.
// Do not handle multiples of 2, 3, and 5.
class PrimeGenerator2 final : public PrimeGeneratorBase {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 2; }

 private:
  std::vector<uint8> flags_;
};
