#include "pet_state.hpp"
#include <cmath>

#include "SDL3/SDL_log.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>

#include <interval.hpp>
#include <pet.hpp>
#include <time.hpp>

void Pet::update() {
  switch (state) {
  case State::IDLE:
    walk.Stop();
    sleep.Stop();
    frame = idle.Play(Time::deltatime);
    break;
  case State::WALK:
    SDL_Log("walk_state: %d\n", walk_state);
    idle.Stop();
    sleep.Stop();
    frame = walk.Play(Time::deltatime);

    if (position_x + 400 >= max_position_x) {
      walk_state = WalkState::LEFT;
    } else if (position_x <= 0) {
      walk_state = WalkState::RIGHT;
    } else if (position_y + 400 >= max_position_y) {
      walk_state = WalkState::UP;
    } else if (position_y <= 0) {
      walk_state = WalkState::DOWN;
    }

    switch (walk_state) {
    case WalkState::LEFT:
      isFlipped = true;
      position_x -= std::ceil(100 * Time::deltatime);
      break;
    case WalkState::RIGHT:
      isFlipped = false;
      position_x += std::ceil(100 * Time::deltatime);
      break;
    case WalkState::UP:
      position_y -= std::ceil(100 * Time::deltatime);
      break;
    case WalkState::DOWN:
      position_y += std::ceil(100 * Time::deltatime);
      break;
    case WalkState::UP_LEFT:
      isFlipped = true;
      position_x -= std::ceil(100 * Time::deltatime);
      position_y -= std::ceil(100 * Time::deltatime);
      break;
    case WalkState::UP_RIGHT:
      isFlipped = false;
      position_x += std::ceil(100 * Time::deltatime);
      position_y -= std::ceil(100 * Time::deltatime);
      break;
    case WalkState::DOWN_LEFT:
      isFlipped = true;
      position_x -= std::ceil(100 * Time::deltatime);
      position_y += std::ceil(100 * Time::deltatime);
      break;
    case WalkState::DOWN_RIGHT:
      isFlipped = false;
      position_x += std::ceil(100 * Time::deltatime);
      position_y += std::ceil(100 * Time::deltatime);
      break;
    }
    break;
  case State::SLEEP:
    idle.Stop();
    walk.Stop();
    frame = sleep.Play(Time::deltatime);
  default:
    break;
  }
}

void Pet::draw(SDL_Renderer *renderer) {
  switch (state) {
  case State::IDLE:
    if (isFlipped)
      SDL_RenderTextureRotated(renderer, idle.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_HORIZONTAL);
    else
      SDL_RenderTextureRotated(renderer, idle.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_NONE);
    break;
  case State::WALK:
    if (isFlipped)
      SDL_RenderTextureRotated(renderer, walk.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_HORIZONTAL);
    else
      SDL_RenderTextureRotated(renderer, walk.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_NONE);
    break;
  case State::SLEEP:
    if (isFlipped)
      SDL_RenderTextureRotated(renderer, sleep.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_HORIZONTAL);
    else
      SDL_RenderTextureRotated(renderer, sleep.tileSet, &frame, nullptr, 0, &center, SDL_FLIP_NONE);
    break;
  default:
    break;
  }
}

Pet::Pet() {
  state_interval.start();
  walk_state_interval.start();
}

Pet::~Pet() {
  state_interval.stop();
  walk_state_interval.stop();
}
