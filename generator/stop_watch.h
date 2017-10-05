#pragma once

#include <chrono>

class StopWatch {
  using Clock = std::chrono::high_resolution_clock;
 public:
  StopWatch();
  double GetTimeInSec() const;

 private:
  Clock::time_point start_;
};
