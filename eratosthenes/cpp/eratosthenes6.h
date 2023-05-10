#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes5.h"

// Generate prime numbers up to x.
// Use initialized list to avoid sieving with small primes. (<= 23)
class Eratosthenes6 final : public Eratosthenes5 {
 public:
  int32 version() override { return 6; }

 private:
  void generateCore(const int64 offset) override;
};
