#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int INITIAL_RADIUS = 30;


void    SDL_RenderDrawCircle(SDL_Renderer* renderer,int circleX,int circleY,int circleradius){
      for(int w=0;w<=circleradius*2;w++){
        for(int h=0;h<=circleradius*2;h++){
            int dx=circleradius - w;
            int dy = circleradius -h;
            if((dx*dx + dy*dy)<=(circleradius*circleradius)){
                SDL_RenderDrawPoint(renderer,circleX+dx,circleY+dy);
            }
        }
    }
}

#undef main
int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    SDL_Event event;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    window = SDL_CreateWindow("Expanding Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() <<endl;
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }

    bool quit = false;
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = INITIAL_RADIUS;
    int expandRate = 20;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

       
       SDL_SetRenderDrawColor(renderer,255, 255, 255, 255);
       SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0,0,200, 255);
    
        SDL_RenderDrawCircle(renderer, centerX,centerY, radius);

       
        radius += expandRate;

        
        if ( centerX + radius >= SCREEN_WIDTH || centerY + radius >= SCREEN_HEIGHT) {
            radius = INITIAL_RADIUS; 
        }

        SDL_RenderPresent(renderer);

        SDL_Delay(10);
    }

  
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}