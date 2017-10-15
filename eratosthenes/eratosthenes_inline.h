uint64 Eratosthenes::PopCnt(uint64 bits) {
  bits = (bits & 0x5555555555555555ULL) + ((bits >> 1) & 0x5555555555555555ULL);
  bits = (bits & 0x3333333333333333ULL) + ((bits >> 2) & 0x3333333333333333ULL);
  bits = (bits & 0x0f0f0f0f0f0f0f0fULL) + ((bits >> 4) & 0x0f0f0f0f0f0f0f0fULL);
  return (bits * 0x0101010101010101ULL) >> (64 - 8);
}

int Eratosthenes::BitToIndex(uint8 b) {
  switch (b) {
  case 1 << 0:  return 0;
  case 1 << 1:  return 1;
  case 1 << 2:  return 2;
  case 1 << 3:  return 3;
  case 1 << 4:  return 4;
  case 1 << 5:  return 5;
  case 1 << 6:  return 6;
  case 1 << 7:  return 7;
  }
  return -1;
}
