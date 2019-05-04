#include <cstdlib>
#include <iostream>
#include <memory>

#include "base.h"
#include "eratosthenes0.h"
#include "eratosthenes1.h"
#include "eratosthenes2.h"
#include "eratosthenes3.h"
#include "eratosthenes4.h"
#include "eratosthenes5.h"
#include "eratosthenes6.h"
#include "gflags/gflags.h"
#include "stop_watch.h"

DEFINE_int32(generator, -1, "Version of the prime generator to use. "
             "The new one is used by default.");
DEFINE_double(time_limit, 5, "Time limit for performance test in sec.");

namespace {

void PerfTest(Eratosthenes* eratosthenes) {
  const struct {
    int64 x;
    int64 pix;
  } test_data[] = {
    {100, 25}, {1000, 168}, {10000, 1229}, {100000, 9592}, {1000000, 78498},
    {10000000, 664579}, {100000000, 5761455}, {1000000000, 50847534},
    {10000000000, 455052511},
  };

  std::cout << "Test\n";
  for (auto data : test_data) {
    StopWatch stop_watch;
    eratosthenes->generate(data.x);
    double t = stop_watch.GetTimeInSec();

    int64 pix = eratosthenes->count();
    if (pix < 0) {
      std::cout << "Give up for pi(" << data.x << ")\n";
      break;
    }
    if (pix != data.pix) {
      std::cout << "pi(" << data.x << ") = " << pix << " != " << data.pix << "\n";
      break;
    }
    std::cout << "pi(" << data.x << ") = " << pix
              << " Time : " << t << " sec\n";
    if (data.x < 10000000000 && t > FLAGS_time_limit) {
      std::cout << "No more try. It will take too long time.\n";
      break;
    }
  }
}

void PerfTestRange(Eratosthenes* eratosthenes) {
  if (eratosthenes->version() < 4)
    return;

  const struct {
    int64 from;
    int64 to;
    int64 primes;
  } test_data[] = {
    {100, 1000, 143}, {1000, 10000, 1061}, {10000, 100000, 8363},
    {100000, 1000000, 68906}, {1000000, 10000000, 586081},
    {10000000, 100000000, 5096876}, {100000000, 1000000000, 45086079},
    // 1000*10^9 - 1001*10^9
    {1000000000000, 1001000000000, 36190991}
  };

  std::cout << "Testing range sieve\n";
  for (auto data : test_data) {
    StopWatch stop_watch;
    eratosthenes->generate(data.from, data.to);
    double t = stop_watch.GetTimeInSec();

    int64 primes = eratosthenes->count();
    if (primes < 0) {
      std::cout << "Give up for pi(" << data.from << ", " << data.to << ")\n";
      break;
    }
    if (primes != data.primes) {
      std::cout << "pi(" << data.from << ", " << data.to << ") = "
                << primes << " != " << data.primes << "\n";
      break;
    }
    std::cout << "pi(" << data.from << ", " << data.to << ") = " << primes
              << " Time : " << t << " sec\n";
    if (t > FLAGS_time_limit) {
      std::cout << "No more try. It will take too long time.\n";
      break;
    }
  }
}

Eratosthenes* CreateEratosthenes(int version) {
  switch (version) {
    case 0: return new Eratosthenes0;
    case 1: return new Eratosthenes1;
    case 2: return new Eratosthenes2;
    case 3: return new Eratosthenes3;
    case 4: return new Eratosthenes4;
    case 5: return new Eratosthenes5;
    case 6: return new Eratosthenes6;
    default:
      return new Eratosthenes5;
  }
  return nullptr;
}

}  // namespace

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::unique_ptr<Eratosthenes> eratosthenes(CreateEratosthenes(FLAGS_generator));
  std::cout << "Eratosthenes version: " << eratosthenes->version() << "\n";

  if (argc < 2) {
    {
      StopWatch stop_watch;
      eratosthenes->initialize();
      std::cout << "initialize: " << stop_watch.GetTimeInSec() << " sec.\n";
    }
    PerfTest(eratosthenes.get());
    if (FLAGS_generator > 4)
      PerfTestRange(eratosthenes.get());
    return 0;
  }

  int64 from = 0;
  int64 to = std::strtoll(argv[1], nullptr, 10);
  if (argc > 2) {
    from = to;
    to = std::strtoll(argv[2], nullptr, 10);
  }
  StopWatch stop_watch;
  eratosthenes->initialize();
  eratosthenes->generate(from, to);
  double t = stop_watch.GetTimeInSec();
  int64 pix = eratosthenes->count();

  if (argc == 2) {
    std::cout << "pi(" << to << ") = " << pix << "\n";
  } else {
    std::cout << "pi(" << from << ", " << to << ") = " << pix << "\n";
  }
  std::cerr << "Time : " << t << " sec\n";

  return 0;
}
