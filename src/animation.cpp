#include <SDL3/SDL_render.h>

#include <animation.hpp>

Animation::Animation(SDL_Texture *tileSet, int totalFrames, int fps) : tileSet(tileSet), totalFrames(totalFrames), fps(fps) {}

Animation::~Animation() {
  SDL_DestroyTexture(tileSet);
}

SDL_FRect Animation::Play(float deltatime) {
  timer += deltatime;
  if (timer >= (1.0f / fps)) {
    timer = 0.0f;
    currentFrame = (currentFrame + 1) % totalFrames;
  }
  return {.x = currentFrame * 400.f, .y = 0, .w = 400.f, .h = 400.f};
}

void Animation::Stop() {
  timer = 0.0f;
  currentFrame = 0;
}

Animation::Animation(Animation &&animation) {
  tileSet = animation.tileSet;
  totalFrames = animation.totalFrames;
  fps = animation.totalFrames;
}

Animation &Animation::operator=(Animation &&other) {
  if (this != &other) {
    SDL_DestroyTexture(tileSet);
    tileSet = other.tileSet;
    totalFrames = other.totalFrames;
    fps = other.fps;
    timer = other.timer;
    currentFrame = other.currentFrame;
    other.tileSet = nullptr;
  }
  return *this;
}
