#include <mutex>
#include <thread>

#include <interval.hpp>

Interval::Interval(std::function<void()> callback, std::chrono::duration<float> interval) : callback(callback), interval(interval) {}

void Interval::start() {
  thread = std::thread([this] {
    running = true;
    while (running) {
      std::unique_lock<std::mutex> lock(mutex);
      cv.wait_for(lock, interval, [this] { return !running; });
      callback();
    }
  });
}

void Interval::stop() {
  if (running) {
    std::unique_lock<std::mutex> lock(mutex);
    running = false;
    lock.unlock();
    cv.notify_one();
    if (thread.joinable()) {
      thread.join();
    }
  }
}
