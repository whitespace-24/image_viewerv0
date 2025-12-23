#include<SDL2/SDL.h>
#include<iostream>
int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* win = SDL_CreateWindow("event_loop", 100, 100, 700, 400, SDL_WINDOW_SHOWN);
    SDL_Event ev;
    bool running = true;
    SDL_Surface* surfexel = SDL_GetWindowSurface(win);
    SDL_FillRect(surfexel, nullptr, SDL_MapRGB(surfexel->format, 0, 0, 100));
    SDL_UpdateWindowSurface(win);
    while(running){ //main loop 
        while (SDL_PollEvent(&ev)!=0){
             if(ev.type == SDL_QUIT){
                running = false;
            }
        }
        // SDL_Delay(100);
     
    }
        SDL_DestroyWindow(win);

}