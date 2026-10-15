#pragma once

#include <chrono>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <thread>

class Interval {
private:
  std::thread thread;
  std::chrono::duration<float> interval;
  std::function<void()> callback;
  bool running = false;
  std::condition_variable cv;
  std::mutex mutex;

public:
  Interval() = default;
  Interval(std::function<void()> callback, std::chrono::duration<float> interval);
  void start();
  void stop();
};
