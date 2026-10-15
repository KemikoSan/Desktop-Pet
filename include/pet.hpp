#pragma once

#include <SDL3/SDL_rect.h>

#include <animation.hpp>
#include <interval.hpp>
#include <pet_state.hpp>
#include <rng.hpp>
#include <vec2.hpp>

using namespace std::chrono_literals;

class Pet {
public:
  State state = State::IDLE;
  WalkState walk_state = WalkState::UP;
  RNG rng;
  Interval state_interval{[&] { state = rng.randomState(); }, 20s};
  Interval walk_state_interval{[&] { walk_state = rng.randomWalkState(); }, 5s};
  int position_x;
  int position_y;
  int max_position_x;
  int max_position_y;
  SDL_FPoint center{200, 200};
  SDL_FRect frame;
  bool isFlipped;
  Animation idle;
  Animation walk;
  Animation sleep;
  void update();
  void draw(SDL_Renderer *renderer);
  Pet();
  ~Pet();
};
