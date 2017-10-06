#pragma once

#include <vector>
#include "base.h"
#include "generator_base.h"

// Generate prime numbers up to x.
// Do not handle even numbers.
class PrimeGenerator1 final : public PrimeGeneratorBase {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 1; }

 private:
  std::vector<bool> flags_;
};
