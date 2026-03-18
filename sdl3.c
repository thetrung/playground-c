#include <SDL3/SDL.h>

int main(int argc, char *argv[]) {
  int ret = SDL_Init(SDL_INIT_VIDEO);
  if (ret != 0) {
    SDL_Log("ret = %d", ret);
    SDL_Log("Init error: %s", SDL_GetError());
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("SDL3 Test", 800, 600, 0);
  SDL_Delay(2000);

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
