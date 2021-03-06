#include <cstdlib>
#include <iostream>
#include <memory>

#include "base.h"
#include "eratosthenes.h"
#include "gflags/gflags.h"
#include "stop_watch.h"

DEFINE_int32(generator, -1, "Version of the prime generator to use. "
             "The new one is used by default.");
DEFINE_double(time_limit, 5, "Time limit for performance test in sec.");

namespace {

void PerfTest(Eratosthenes& eratosthenes) {
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
    eratosthenes.generate(data.x);
    double t = stop_watch.GetTimeInSec();

    int64 pix = eratosthenes.count();
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

void PerfTestRange(Eratosthenes& eratosthenes) {
  if (eratosthenes.version() < 4)
    return;

  const struct {
    int64 from;
    int64 to;
    int64 primes;
  } test_data[] = {
    {100, 1000, 143}, {1000, 10000, 1061}, {10000, 100000, 8363},
    {100000, 1000000, 68906}, {1000000, 10000000, 586081},
    {10000000, 100000000, 5096876}, {100000000, 1000000000, 45086079},
    // [x, x+10^9] for x=10^{12,13,14,15}
    {1000000000000, 1001000000000, 36190991},
    {10000000000000, 10001000000000, 33405006},
    {100000000000000, 100001000000000, 31019409},
    {1000000000000000, 1000001000000000, 28946421},
  };

  std::cout << "Testing range sieve\n";
  for (auto data : test_data) {
    StopWatch stop_watch;
    eratosthenes.generate(data.from, data.to);
    double t = stop_watch.GetTimeInSec();

    int64 primes = eratosthenes.count();
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

void RunPerfTests(Eratosthenes& eratosthenes) {
  std::cout << "Test and measure performance of eratosthenes version: "
            << eratosthenes.version() << "\n";
  {
    StopWatch stop_watch;
    eratosthenes.initialize();
    std::cout << "initialize: " << stop_watch.GetTimeInSec() << " sec.\n";
  }
  PerfTest(eratosthenes);
  if (eratosthenes.version() >= 4)
    PerfTestRange(eratosthenes);
}

void CountPrimes(Eratosthenes& eratosthenes, int64 from, int64 to) {
  StopWatch stop_watch;
  eratosthenes.initialize();
  eratosthenes.generate(std::max<int64>(from, 0), to);
  double t = stop_watch.GetTimeInSec();
  int64 pix = eratosthenes.count();

  if (from < 0) {
    std::cout << "pi(" << to << ") = " << pix << "\n";
  } else {
    std::cout << "pi(" << from << ", " << to << ") = " << pix << "\n";
  }
  std::cerr << "Time : " << t << " sec\n";
}

}  // namespace

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::unique_ptr<Eratosthenes> eratosthenes(Eratosthenes::Create(FLAGS_generator));
  if (!eratosthenes) {
    std::cerr << "Version " << FLAGS_generator << " is not supported\n";
    return 0;
  }
  
  if (argc < 2) {
    RunPerfTests(*eratosthenes);
    return 0;
  }

  int64 from = -1;
  int64 to = std::strtoll(argv[1], nullptr, 10);
  if (argc > 2) {
    from = to;
    to = std::strtoll(argv[2], nullptr, 10);
  }
  CountPrimes(*eratosthenes, from, to);

  return 0;
}
