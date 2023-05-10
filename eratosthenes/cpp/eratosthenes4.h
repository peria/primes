#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
// Segment sieved area, with smaller memory storage.
class Eratosthenes4 : public Eratosthenes {
 public:
  void generate(const int64 x) override;
  void generate(const int64 from, const int64 to) override;
  int64 count() override;
  int32 version() override { return 4; }

 protected:
  virtual void generateCore(const int64 offset);
  virtual void initFlags(const int64 from_rem, const int64 to,
                         const int64 offest, const int64 size);
  virtual void generateSmall(const uint64 offset, const int64 sqrt_to);

  int64 num_primes_ = -1;
  std::vector<uint8> sflags_;
  std::vector<uint8> flags_;
  std::vector<uint64> indecies_;
};
