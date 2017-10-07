#include "generator_base.h"

#include <iostream>

uint64 PrimeGeneratorBase::PopCnt(uint64 bits) {
  bits = (bits & 0x5555555555555555ULL) + ((bits >> 1) & 0x5555555555555555ULL);
  bits = (bits & 0x3333333333333333ULL) + ((bits >> 2) & 0x3333333333333333ULL);
  bits = (bits & 0x0f0f0f0f0f0f0f0fULL) + ((bits >> 4) & 0x0f0f0f0f0f0f0f0fULL);
  return (bits * 0x0101010101010101ULL) >> (64 - 8);
}
