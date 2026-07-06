#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu;

int main() {
    // INITIALIZATION
    Renderer render;
    render.Initialize("Game Engine", 1920, 1024);

    // std::cout << sizeof(Vector2) << std::endl;
    Vector2 vel{ 0.5f, 0.0f };

    std::vector<Vector2> v;

    for (int i = 0; i < 300; i++) {
        v.push_back({ nu::RandomFloat(1920), nu::RandomFloat(1024) });
    }

    // GAME LOOP
    bool quit = false;

    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // RENDER
        render.SetColor(0.0f, 0.0f, 0.0f);
        render.Clear();

        /*for (int i = 0; i < 10; i++) {
            render.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            render.DrawLine(nu::RandomFloat(1920), nu::RandomFloat(1024), nu::RandomFloat(1920), nu::RandomFloat(1024));
        }*/

        for (size_t i = 0; i < v.size(); i++) {
            render.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());

            v[i] = v[i] + vel;
            render.DrawPoint(v[i].x, v[i].y);
        }

        /*for (int i = 0; i < 5; i++) {
            render.SetColor(nu::RandomFloat(), nu::RandomFloat(), nu::RandomFloat());
            render.DrawRect(nu::RandomFloat(1920), nu::RandomFloat(1024), 100, 100);
        }*/

        render.Present();
    }

    // SHUTDOWN
    render.Shutdown();

    return 0;
}