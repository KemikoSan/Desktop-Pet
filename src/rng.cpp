#include <random>

#include <pet_state.hpp>
#include <rng.hpp>

int RNG::randomInt(int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

float RNG::randomFloat(float min, float max) {
  std::uniform_real_distribution<float> distribution(min, max);
  return distribution(generator);
}

State RNG::randomState() {
  std::uniform_int_distribution<int> distribution(0, 2);
  return State{distribution(generator)};
}

WalkState RNG::randomWalkState() {
  std::uniform_int_distribution<int> distribution(0, 7);
  return WalkState{distribution(generator)};
}
