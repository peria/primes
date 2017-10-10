#include <cstdlib>
#include <iostream>
#include <memory>

#include "base.h"
#include "generators.h"
#include "gflags/gflags.h"
#include "stop_watch.h"

DEFINE_int32(generator, -1, "Version of the prime generator to use. "
             "The new one is used by default.");
DEFINE_double(time_limit, 5, "Time limit for performance test in sec.");

namespace {

void PerfTest(PrimeGeneratorBase* generator) {
  const struct {
    int64 x;
    int64 pix;
  } test_data[] = {
    {100, 25}, {1000, 168}, {10000, 1229}, {100000, 9592}, {1000000, 78498},
    {10000000, 664579}, {100000000, 5761455}, {1000000000, 50847534},
    {10000000000, 455052511}, {100000000000, 4118054813},
  };

  std::cout << "Using prime generator version " << generator->version() << ".\n";
  for (auto data : test_data) {
    StopWatch stop_watch;
    generator->generate(data.x);
    double t = stop_watch.GetTimeInSec();

    int64 pix = generator->count();
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
    if (t > FLAGS_time_limit) {
      std::cout << "No more try. It will take too long time.\n";
      break;
    }
  }
}

PrimeGeneratorBase* CreatePrimeGenerator(int version) {
  switch (version) {
    case 0: return new PrimeGenerator0;
    case 1: return new PrimeGenerator1;
    case 2: return new PrimeGenerator2;
    case 3: return new PrimeGenerator3;
    default:
      return new PrimeGenerator3;
  }
  return nullptr;
}

}  // namespace

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  std::unique_ptr<PrimeGeneratorBase> generator(CreatePrimeGenerator(FLAGS_generator));

  if (argc < 2) {
    PerfTest(generator.get());
    return 0;
  }

  int64 x = std::strtoll(argv[1], nullptr, 10);
  StopWatch stop_watch;
  generator->generate(x);
  double t = stop_watch.GetTimeInSec();
  int64 pix = generator->count();

  std::cout << "pi(" << x << ") = " << pix << "\n";
  std::cerr << "Time : " << t << " sec\n";

  return 0;
}
