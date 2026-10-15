#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class Animation {
private:
  int totalFrames = 0;
  int currentFrame = 0;
  int fps = 0;
  float timer = 0.f;

public:
  SDL_Texture *tileSet = nullptr;
  SDL_FRect Play(float deltatime);
  void Stop();
  Animation() = default;
  Animation(SDL_Texture *tileSet, int totalFrames, int fps);
  Animation(const Animation &) = delete;
  Animation &operator=(const Animation &) = delete;
  Animation(Animation &&animation);
  Animation &operator=(Animation &&other);
  ~Animation();
};
