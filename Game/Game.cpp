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

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        render.SetColor(0, 0, 0);
        render.Clear();

        for (int i = 0; i < 10; i++) {
            render.SetColor(rand() % 256, rand() % 256, rand() % 256);
            render.DrawLine(rand() % 1920, rand() % 1024, rand() % 1920, rand() % 1024);
        }

        for (int i = 0; i < 1000; i++) {
            render.SetColor(rand() % 256, rand() % 256, rand() % 256);
            render.DrawPoint(rand() % 1920, rand() % 1024);
        }

        for (int i = 0; i < 5; i++) {
            render.SetColor(rand() % 256, rand() % 256, rand() % 256);
            render.DrawRect(rand() % 1920, rand() % 1024, 100, 100);
        }

        render.Present();
    }

    render.Shutdown();

    return 0;
}