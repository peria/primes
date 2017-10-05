#pragma once

#include <cstdint>
#include <array>

using uint64 = std::uint64_t;
using uint32 = std::uint32_t;
using uint8 = std::uint8_t;
using int64 = std::int64_t;
using int32 = std::int32_t;

class PrimeGenerator {
 public:
  virtual int64 count(int64 from, int64 to) = 0;
};

class PrimeGenerator0 final : public PrimeGenerator {
 public:
  int64 count(int64 from, int64 to) override;

 private:
  std::array<uint8, 100> flags_;
};
