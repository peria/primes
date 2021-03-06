#include "eratosthenes.h"

#include "eratosthenes0.h"
#include "eratosthenes1.h"
#include "eratosthenes2.h"
#include "eratosthenes3.h"
#include "eratosthenes4.h"
#include "eratosthenes5.h"
#include "eratosthenes6.h"

Eratosthenes* Eratosthenes::Create(int version) {
  switch (version) {
    case 0: return new Eratosthenes0;
    case 1: return new Eratosthenes1;
    case 2: return new Eratosthenes2;
    case 3: return new Eratosthenes3;
    case 4: return new Eratosthenes4;
    case 5: return new Eratosthenes5;
    case 6: return new Eratosthenes6;
    default:
      return new Eratosthenes6;
  }
  return nullptr;
}

