#include <iostream>
using namespace std;
#include <SDL2/SDL.h>
#include <math.h>
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int RADIUS = 60;
#undef main
void SDL_DrawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int i = 0; i <= radius * 2; i++)
    {
        for (int j = 0; j <= radius * 2; j++)
        {
            int dx = radius - i;
            int dy = radius - j;
            if ((dx * dx + dy * dy) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}
int main()
{
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
    }

    window = SDL_CreateWindow("Expanding Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
    }

    int centerX = SCREEN_WIDTH / 2;
    int centerY = SCREEN_HEIGHT / 2;
    int radius = RADIUS;
    SDL_SetRenderDrawColor(renderer, 225, 165, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 128, 0, 128, 255);

    SDL_DrawCircle(renderer, centerX, centerY, radius);

    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event e;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_Delay(3000);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
