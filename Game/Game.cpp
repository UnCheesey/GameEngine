#include "Engine.h"
#include "Player.h"

#include <iostream>
#include <vector>

using namespace nu;

int main() {

    // INITIALIZATION
    engine.Initialize();

    Mesh mesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{ -2, -2 }, Vector2{ 2, 0 } } , Color{ 0.0f, 0.0f, 1.0f } };
    Player player{ Transform{Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f }, std::vector<Mesh>{ mesh } };

    // PAINT
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
        
        // Engine
        engine.Update();

        player.SetRotation(player.GetTransform().rotation + (90.0f * engine.GetTime().GetDeltaTime()));

        player.Update(engine.GetTime().GetDeltaTime());

        if (engine.GetInput().GetButtonDown(nu::Input::MouseButton::Left)) {

            if(points.empty()){
                points.push_back(engine.GetInput().GetMousePos());
            }else {

                Vector2 v = points.back() - engine.GetInput().GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(engine.GetInput().GetMousePos());
                }
            }
        }

        if (engine.GetInput().GetButtonDown(nu::Input::MouseButton::Right)) {
                if (!points.empty()) {
                    points.pop_back();
                }
            
        }

        

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColor(0.5f, 0.2f, 0.4f);
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        // character
        player.Draw(engine.GetRenderer());

        // PRESENT
        engine.GetRenderer().Present();
    }

    // SHUTDOWN
    

    return 0;
}