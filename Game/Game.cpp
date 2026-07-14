#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu;

int main() {

    // INITIALIZATION
    Renderer render;
    render.Initialize("Game Engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    nu::Time time;

    Mesh mesh{ { Vector2{ -3, 3 }, Vector2{ 3, 3 }, Vector2{ 0, 0 } } , Color{ 0.0f, 0.0f, 1.0f } };
    Actor player{ Transform{Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh>{ mesh } };

    Vector2 position{ 640.0f, 512.0f };
    Vector2 velocity{ 0.0f, 0.0f };
    float speed = 800.0f;

    std::vector<Vector2> points;

    Vector2 mousePos;

    // MAIN LOOP
    bool quit = false;
    while (!quit) {

        // UPDATE
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) {
                quit = true;
            }

            if (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE) {
                quit = true;
            }
        }
        
        // Enginge
        input.Update();
        time.Tick();

        if (input.GetButtonDown(nu::Input::MouseButton::Left)) {

            if(points.empty()){
                points.push_back(input.GetMousePos());
            }else {

                Vector2 v = points.back() - input.GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(input.GetMousePos());
                }
            }
        }

        if (input.GetButtonDown(nu::Input::MouseButton::Right)) {
                if (!points.empty()) {
                    points.pop_back();
                }
            
        }

        Vector2 force{ 0.0f, 0.0f };
        if (input.GetKeyDown(SDL_SCANCODE_W)) force.y = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_A)) force.x = -speed;
        if (input.GetKeyDown(SDL_SCANCODE_S)) force.y = +speed;
        if (input.GetKeyDown(SDL_SCANCODE_D)) force.x = +speed;

        player.SetVelocity(player.GetVelocity() + (force * time.GetDeltaTime()));
        player.Update(time.GetDeltaTime());

        // RENDER
        render.SetColor(0.0f, 0.0f, 0.0f);
        render.Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            render.SetColor(0.5f, 0.2f, 0.4f);
            render.DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        // character
        player.Draw(render);

        // PRESENT
        render.Present();
    }

    // SHUTDOWN
    render.Shutdown();

    return 0;
}