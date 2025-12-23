#include <SDL2/SDL.h>
#include <iostream>
int main(){
SDL_Init(SDL_INIT_EVERYTHING);
SDL_Window* win = SDL_CreateWindow("First window", 100, 100, 500, 400, SDL_WINDOW_SHOWN);
if(!win) { 
    std::cout<< SDL_GetError() << std::endl;
}
SDL_Surface* winsurface= SDL_GetWindowSurface(win);
// SDL_UpdateWindowSurface(win);
SDL_FillRect(winsurface, nullptr, SDL_MapRGB(winsurface->format, 255, 90, 120));
SDL_UpdateWindowSurface(win);
SDL_Delay(3000);
SDL_DestroyWindow(win);
win = nullptr;
winsurface =nullptr;
SDL_Quit();
}