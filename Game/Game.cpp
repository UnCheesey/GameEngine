#include "Engine.h"
#include "SDL3/SDL.h"
#include "Renderer.h"

#include <iostream>

int main() {
    nu::Renderer render;
    render.Initialize("Game Engine", 1920, 1024);

    // handle events
    SDL_Event e;
    bool quit = false;

    // Define a rectangle
    SDL_FRect greenSquare{ 270, 190, 200, 200 };

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        render.SetColor(0, 0, 0);
        render.Clear();

        for (int i = 0; i < 1000; i++) {
            render.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
            render.DrawPoint(rand() % 1280, rand() % 1024);
        }

        render.SetColor(rand() % 256, rand() % 256, rand() % 256, 255);
        render.DrawFillRect(rand() % 256, rand() % 256, rand() % 256, rand() % 256);

        render.Present();
    }

    render.Shutdown();

    return 0;
}