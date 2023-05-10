#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes4.h"

// Generate prime numbers up to x.
// Use initialized list to avoid sieving with small primes. (<= 23)
class Eratosthenes5 : public Eratosthenes4 {
 public:
  void initialize() override;
  void generate(const int64 from, const int64 to) override;
  int32 version() override { return 5; }

 protected:
  std::vector<uint8> initial_;

 private:
  void initFlags(const int64 from_rem, const int64 to,
                 const int64 offest, const int64 size) override;
  void generateSmall(const uint64 offset, const int64 sqrt_to) override;
};
