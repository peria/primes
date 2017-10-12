#pragma once

#include <vector>
#include "base.h"
#include "generator_base.h"

// Generate prime numbers up to x.
// Segment sieved area, with smaller memory storage.
class PrimeGenerator4 final : public PrimeGeneratorBase {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 4; }

 private:
  void generateSmall();
  void generateCore(const int64 offset);

  int64 num_primes_ = -1;
  std::vector<uint8> sflags_;
  std::vector<uint8> flags_;
  std::vector<uint32> indecies_;
};
