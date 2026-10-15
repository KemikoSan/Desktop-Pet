#pragma once

#include <pet_state.hpp>
#include <random>

class RNG {
private:
  std::mt19937 generator;

public:
  RNG() = default;
  int randomInt(int min, int max);
  float randomFloat(float min, float max);
  State randomState();
  WalkState randomWalkState();
};
