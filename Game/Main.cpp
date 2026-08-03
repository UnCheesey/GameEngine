#include "Engine.h"

#include "SpaceGame.h"

#include <iostream>
#include <vector>
#include <map>

// Files use namespace fe::

using namespace nu;

int main() {
        
    // ENGINE INITIALIZATION
    Engine::Get().Initialize();

    // SPACE GAME INITIALIZATION
    SpaceGame game;
    game.Initialize();

    // PAINT INITIALIZATION
    /*std::vector<Vector2> points;
    Vector2 mousePos = { 0,0 };*/

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
        
        // Engine Update (audio, input, time)
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();
        game.Update(dt);

        // PAINT LOOP
        {// LINE DRAWING DRAW
        /*if (Engine::Get().GetInput().GetButtonDown(nu::Input::MouseButton::Left)) {

            if(points.empty()){
                points.push_back(Engine::Get().GetInput().GetMousePos());
            }else {

                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePos());
                }
            }
        }*/

        // LINE DRAWING ERASE
        /*if (Engine::Get().GetInput().GetButtonDown(nu::Input::MouseButton::Right)) {
                if (!points.empty()) {
                    points.pop_back();
                }
        }*/

        // LINE DRAWING ADD POINTS
        /*for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(0.5f, 0.2f, 0.4f);
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }*/
        }
        
        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        

        // DRAW SCENE
        game.Draw(Engine::Get().GetRenderer());
        
        // PRESENT
        Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();
    

    return 0;
}