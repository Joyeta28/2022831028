#include<iostream>
using namespace std;
#include<SDL2/SDL.h>
#include<math.h>
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;
const int RADIUS=60;
#undef main
int main(){
   SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
   

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Expanding Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() <<endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
    }
   
    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = RADIUS;
     SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);

    for(int w=0;w<=radius*2;w++){
        for(int h=0;h<=radius*2;h++){
            int dx=radius - w;
            int dy = radius -h;
            if((dx*dx + dy*dy)<=(radius*radius)){
                SDL_RenderDrawPoint(renderer,centerX+dx,centerY+dy);
            }
        }
    }
   SDL_RenderPresent(renderer);

    bool quit= false;
    SDL_Event e;
    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                quit=true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
return 0;

}

