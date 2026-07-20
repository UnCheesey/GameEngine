#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include <fmod.hpp>

#include <iostream>
#include <vector>

using namespace nu;

int main() {

    // INITIALIZATION
    engine.Initialize();

    // SOUND SYSTEM CREATION
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);

    Mesh mesh{ { Vector2{ 2, 0 }, Vector2{ -2, 2 }, Vector2{ -1, 0 }, Vector2{ -2, -2 }, Vector2{ 2, 0 } } , Color{ 0.0f, 0.0f, 1.0f } };
    Model model{ std::vector<Mesh>{mesh} };

    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.tag = "Player01";
    playerDesc.name = "Timothy";
    playerDesc.speed = 2000.0f;
    playerDesc.velocity = {0, 0};
    playerDesc.transform = Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.model = model;

    Player* player = new Player(playerDesc);
    scene.AddActor(player);


    EnemyDesc enemyDesc;
    enemyDesc.tag = "Enemy01";
    enemyDesc.name = "Tommy";
    enemyDesc.speed = 2000.0f;
    enemyDesc.velocity = { 0,0 };
    enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::engine.GetRenderer().GetWidth()), nu::RandomFloat((float)nu::engine.GetRenderer().GetHeight())}, 90.0f, 10.0f };
    enemyDesc.model = model;

    Enemy* enemy = new Enemy(enemyDesc);
    scene.AddActor(enemy);

    // AUDIO ADDING
    std::vector<FMOD::Sound*> sounds;
    FMOD::Sound* sound = nullptr;

    audio->createSound("snare.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("bass.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("clap.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("open-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("close-hat.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

    audio->createSound("test.wav", FMOD_DEFAULT, 0, &sound);
    sounds.push_back(sound);

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

        float dt = engine.GetTime().GetDeltaTime();


        //player.Update(engine.GetTime().GetDeltaTime());
        scene.Update(dt);

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

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_1)) {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_2)) {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_3)) {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_4)) {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_5)) {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        if (engine.GetInput().GetKeyPressed(SDL_SCANCODE_6)) {
            audio->playSound(sounds[5], nullptr, false, nullptr);
        }
        

        // RENDER
        engine.GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        engine.GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            engine.GetRenderer().SetColor(0.5f, 0.2f, 0.4f);
            engine.GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        // character
        //player.Draw(engine.GetRenderer());
        //enemy.Draw(engine.GetRenderer());
        scene.Draw(engine.GetRenderer());
        audio->update();

        // PRESENT
        engine.GetRenderer().Present();
    }

    // SHUTDOWN
    

    return 0;
}