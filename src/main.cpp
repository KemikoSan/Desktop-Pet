#include <array>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_image/SDL_image.h>

#include <animation.hpp>
#include <file.hpp>
#include <filesystem>
#include <pet.hpp>
#include <time.hpp>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *window = SDL_CreateWindow("Desktop-Pets", 400, 400, SDL_WINDOW_TRANSPARENT | SDL_WINDOW_BORDERLESS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALWAYS_ON_TOP);
  SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
  SDL_Event Event;

  const SDL_DisplayMode *display = SDL_GetCurrentDisplayMode(SDL_GetPrimaryDisplay());

  SDL_SetRenderVSync(renderer, 1);

  bool bordered = false;
  bool IsRunning = true;

  Pet pet;
  pet.max_position_x = display->w;
  pet.max_position_y = display->h;
  SDL_GetWindowPosition(window, &pet.position_x, &pet.position_y);

  // loading assets
  for (const auto &entry : std::filesystem::directory_iterator("assets")) {
    std::string path = entry.path().string();
    int last = path.find_last_of("/");
    std::array<int, 2> values = find_values(path.substr(last + 1, path.size()));

    if (path.contains("idle")) {
      pet.idle = Animation{IMG_LoadTexture(renderer, path.c_str()), values[0], values[1]};
    } else if (path.contains("walk")) {
      pet.walk = Animation{IMG_LoadTexture(renderer, path.c_str()), values[0], values[1]};
    } else if (path.contains("sleep")) {
      pet.sleep = Animation{IMG_LoadTexture(renderer, path.c_str()), values[0], values[1]};
    }
    if (pet.idle.tileSet && pet.walk.tileSet && pet.sleep.tileSet) {
      break;
    }
  }

  while (IsRunning) {
    while (SDL_PollEvent(&Event)) {
      if (Event.type == SDL_EVENT_QUIT) {
        IsRunning = false;
      }
      if (Event.type == SDL_EVENT_KEY_DOWN) {
        if (Event.key.scancode == SDL_SCANCODE_F11) {
          bordered = !bordered;
          SDL_SetWindowBordered(window, bordered);
        }
        if (Event.key.scancode == SDL_SCANCODE_ESCAPE) {
          IsRunning = false;
        }
      }
      if (Event.type == SDL_EVENT_WINDOW_MOVED) {
        SDL_GetWindowPosition(window, &pet.position_x, &pet.position_y);
      }
    }
    Time::update();
    pet.update();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    pet.draw(renderer);
    SDL_RenderPresent(renderer);

    SDL_SetWindowPosition(window, pet.position_x, pet.position_y);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
