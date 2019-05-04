#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
// Use initialized list to avoid sieving with small primes. (<= 23)
class Eratosthenes6 final : public Eratosthenes {
public:
  void initialize() override;
  void generate(const int64 x) override;
  void generate(const int64 from, const int64 to) override;
  int64 count() override;
  int32 version() override { return 6; }

 private:
  void initFlags(const int64 from_rem, const int64 to,
                 const int64 offest, const int64 size);
  void generateSmall(const uint64 offset, const int64 sqrt_to);
  void generateCore(const int64 offset);

  int64 num_primes_ = -1;
  std::vector<uint8> sflags_;
  std::vector<uint8> flags_;
  std::vector<uint64> indecies_;
  std::vector<uint8> initial_;
};
