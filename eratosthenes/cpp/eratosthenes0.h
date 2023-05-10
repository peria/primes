#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
class Eratosthenes0 final : public Eratosthenes {
 public:
  void generate(const int64 x) override;
  int64 count() override;
  int32 version() override { return 0; }

 private:
  std::vector<bool> flags_;
};
