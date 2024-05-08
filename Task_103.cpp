#include<iostream>
#include<SDL2/SDL.h>
using namespace std;

#undef main
const int SCREEN_WIDTH =680;
const int SCREEN_HEIGHT = 480;
const int RADIUS=30;
const int SPEED=10;
const int SPEED2=2;


void SDL_DrawCircle(SDL_Renderer* renderer,int circleX,int circleY,int circleradius){
    for(int i = 0;i<=2*circleradius;i++){
        for(int j = 0; j<= 2*circleradius;j++){
            int dx=circleradius-i;
            int dy = circleradius - j;
            if(dx*dx + dy*dy <= circleradius*circleradius){
                SDL_RenderDrawPoint(renderer,circleX+dx,circleY-dy);
            }
        }
    }
}

int main(){
    SDL_Init(SDL_INIT_EVERYTHING);
    if(SDL_Init(SDL_INIT_VIDEO<0)){
        cout<<"SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    SDL_Window *window = nullptr;
    SDL_Renderer* renderer = nullptr;

    window = SDL_CreateWindow("Moving Circle",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(window == nullptr){
        cout<<"Window could not be created! SDL_Error: "<<SDL_GetError();
        return 1;
    }
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr){
        cout<< "Renderer could not be created! SDL_Error: "<<SDL_GetError();
        return 1;
    }
    int circleX1=SCREEN_WIDTH/2 - RADIUS;
    int circleY1=SCREEN_HEIGHT/2 - RADIUS;
    int circleX2=SCREEN_WIDTH/2-RADIUS;
    int circleY2=SCREEN_HEIGHT/2-(3*RADIUS);
    int circleradius=RADIUS;

     bool running = true;
    SDL_Event event;
    while(running){
        while(SDL_PollEvent(&event) !=0){
            if(event.type == SDL_QUIT){
                running = false;
                break;
            }
            else if(event.type == SDL_KEYDOWN){
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    circleY1-=SPEED;
                    break;
                case SDLK_DOWN:
                    circleY1 +=SPEED;
                    break;
                case SDLK_LEFT:
                    circleX1-=SPEED;
                    break;
                case SDLK_RIGHT:
                    circleX1+=SPEED;
                    break;
                
                default:
                    break;
                }
            }
        }
        circleX2+=SPEED2;
        if( circleX2 + circleradius >= SCREEN_WIDTH ){
            circleX2=circleradius;
        }

          bool collision = false;
        int dx = circleX1 - circleX2;
        int dy = circleY1 - circleY2;
       
        if ((dx*dx +dy*dy) <= circleradius*circleradius ) {
            collision = true;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 200, 255); 
        SDL_DrawCircle(renderer, circleX1, circleY1, circleradius);
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
        SDL_DrawCircle(renderer, circleX2, circleY2, circleradius);

        
        if (collision) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            SDL_DrawCircle(renderer, circleX1, circleY1, circleradius);
            SDL_DrawCircle(renderer, circleX2, circleY2, circleradius);
        }
        
        SDL_RenderPresent(renderer);
    }
       
        SDL_Delay(10);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    return 0;
}

