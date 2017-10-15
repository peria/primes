#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
// Do not handle even numbers.
class Eratosthenes1 final : public Eratosthenes {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 1; }

 private:
  std::vector<bool> flags_;
};
