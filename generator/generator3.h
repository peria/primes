#pragma once

#include <vector>
#include "base.h"
#include "generator_base.h"

// Generate prime numbers up to x.
// Segment sieved area.
class PrimeGenerator3 final : public PrimeGeneratorBase {
 public:
  void generate(int64 x) override;
  int64 count() override;
  int32 version() override { return 3; }

 private:
  void generateSmall(const uint64 segment_size, uint64 sqrt_xi);
  void generateCore(uint8* flags, const uint64 size, uint64 sqrt_xi);

  std::vector<uint8> flags_;
  std::vector<uint32> indecies_;
};
