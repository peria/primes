#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
// Segment sieved area, with smaller memory storage.
class Eratosthenes4 final : public Eratosthenes {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 4; }

 private:
  void initFlags(const int64 x, const int64 offest, const int64 size);
  void generateSmall(const int64 sqrt_x);
  void generateCore(const int64 offset);

  int64 num_primes_ = -1;
  std::vector<uint8> sflags_;
  std::vector<uint8> flags_;
  std::vector<uint32> indecies_;
};
