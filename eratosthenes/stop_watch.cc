#include "stop_watch.h"
using namespace std::chrono;

StopWatch::StopWatch() : start_(Clock::now()) {}

double StopWatch::GetTimeInSec() const {
  auto duration = Clock::now() - start_;
  return duration_cast<microseconds>(duration).count() * 1e-6;
}
