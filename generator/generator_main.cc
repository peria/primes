#include <iostream>
#include <memory>

#include "base.h"
#include "generators.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "stop_watch.h"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\n"
              << " " << argv[0] << " number\n";
    return 0;
  }

  std::unique_ptr<PrimeGeneratorBase> generator;
  const int64 x = 100000000;
  generator.reset(new PrimeGenerator1(x));
  {
    StopWatch stop_watch;
    generator->sieve();
    std::cerr << "Time : " << stop_watch.GetTimeInSec() << " sec\n";
  }
  int64 pix = generator->count();
  std::cout << "pi(" << x << ") = " << pix << " (expect: 5761455)\n";

  return 0;
}
