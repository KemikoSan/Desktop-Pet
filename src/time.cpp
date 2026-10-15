#include "SDL3/SDL_timer.h"

#include <time.hpp>

float Time::deltatime = 0.0f;

void Time::update() {
  static Uint64 lastCounter = SDL_GetPerformanceCounter();
  Uint64 currentCounter = SDL_GetPerformanceCounter();
  Uint64 frequency = SDL_GetPerformanceFrequency();
  Time::deltatime = ((currentCounter - lastCounter) / static_cast<float>(frequency));
  lastCounter = currentCounter;
}
