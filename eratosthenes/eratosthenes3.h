#pragma once

#include <vector>
#include "base.h"
#include "eratosthenes.h"

// Generate prime numbers up to x.
// Segment sieved area.
class Eratosthenes3 final : public Eratosthenes {
 public:
  void generate(const int64 x) override;
  void generate(const int64, const int64) override { NOTIMPLEMENTED(); }
  int64 count() override;
  int32 version() override { return 3; }

 private:
  void initFlags(const int64 x, const int64 size);
  void generateSmall(const int64 sqrt_x);
  void generateCore(uint8* flags, const uint64 size);

  std::vector<uint8> sflags_;
  std::vector<uint8> flags_;
  std::vector<uint32> indecies_;
};
