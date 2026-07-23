#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "Assets.h"
#include "File.h"

#include <fmod.hpp>

#include <iostream>
#include <vector>

using namespace nu;

int main() {

    // get current working directory
    std::cout << "Directory Operations:\n";
    std::cout << "Working directory: " << fe::GetWorkingDirectory() << "\n";

    // set working directory (current working directory + "Assets")
    std::cout << "Setting directory to 'Assets'...\n";
    fe::SetWorkingDirectory("Assets");
    std::cout << "New directory: " << fe::GetWorkingDirectory() << "\n\n";

    // get filenames in the working directory
    std::cout << "Files in Directory:\n";
    auto filenames = fe::GetFilesInDirectory(fe::GetWorkingDirectory());
    for (const auto& filename : filenames)
    {
        std::cout << filename << "\n";
    }
    std::cout << "\n";

    // get filename info
    if (!filenames.empty())
    {
        // get filename
        std::string str = fe::GetFilename(filenames[0]);
        std::cout << "Filename: " << str << "\n";

        // get extension
        str = fe::GetFileExtension(filenames[0]);
        std::cout << "Extension: " << str << "\n";

        // get filename no extension
        str = fe::GetFilenameNoExtension(filenames[0]);
        std::cout << "Filename No Extension: " << str << "\n\n";
    }

    // read and display text file
    std::cout << "Text File Reading:\n";
    std::string str;
    if (fe::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // write to text file
    std::cout << "Text File Writing:\n";
    fe::WriteTextFile("test.txt", " Hello, World!", true);
    if (fe::ReadTextFile("test.txt", str))
    {
        std::cout << str << "\n";
    }

    // INITIALIZATION
    Engine::Get().Initialize();

    // SOUND SYSTEM INITIALIZATION
    FMOD::System* audio;
    FMOD::System_Create(&audio);

    void* extradriverdata = nullptr;
    audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
        
    Scene scene;

    PlayerDesc playerDesc;
    playerDesc.name = "Player";
    playerDesc.model = assets::playerModel;
    playerDesc.transform = Transform{ Vector2 { 640.0f, 512.0f }, 0.0f, 15.0f };
    playerDesc.velocity = Vector2{ 0.0f, 0.0f };
    playerDesc.damping = 2.0f;
    playerDesc.speed = 2500.0f;

    Player* player = new Player(playerDesc);
    scene.AddActor(player);

    for (int i = 0; i < 20; i++) {
        EnemyDesc enemyDesc;
        enemyDesc.name = "Enemy";
        enemyDesc.model = assets::enemyModel;
        enemyDesc.transform = Transform{ Vector2{ nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetWidth()), nu::RandomFloat((float)nu::Engine::Get().GetRenderer().GetHeight())}, 90.0f, 10.0f };
        enemyDesc.damping = 3.0f;
        enemyDesc.speed = RandomFloat(1000.0f, 2500.0f);


        Enemy* enemy = new Enemy(enemyDesc);
        scene.AddActor(enemy);
    }

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

    audio->createSound("vista.wav", FMOD_DEFAULT, 0, &sound);

    // PAINT
    std::vector<Vector2> points;

    Vector2 mousePos;

    // MAIN LOOP
    bool quit = false;

    audio->playSound(sound, nullptr, false, nullptr);
    
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
        Engine::Get().Update();
        audio->update();

        float dt = Engine::Get().GetTime().GetDeltaTime();

        //player.Update(Engine::Get().GetTime().GetDeltaTime());
        scene.Update(dt);

        if (Engine::Get().GetInput().GetButtonDown(nu::Input::MouseButton::Left)) {

            if(points.empty()){
                points.push_back(Engine::Get().GetInput().GetMousePos());
            }else {

                Vector2 v = points.back() - Engine::Get().GetInput().GetMousePos();
                if (v.Length() > 10.0f) {
                    points.push_back(Engine::Get().GetInput().GetMousePos());
                }
            }
        }

        if (Engine::Get().GetInput().GetButtonDown(nu::Input::MouseButton::Right)) {
                if (!points.empty()) {
                    points.pop_back();
                }
            
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_1)) {
            audio->playSound(sounds[0], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_2)) {
            audio->playSound(sounds[1], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_3)) {
            audio->playSound(sounds[2], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_4)) {
            audio->playSound(sounds[3], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_5)) {
            audio->playSound(sounds[4], nullptr, false, nullptr);
        }

        if (Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_6)) {
            audio->playSound(sounds[5], nullptr, false, nullptr);
        }
        

        // RENDER
        Engine::Get().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        Engine::Get().GetRenderer().Clear();

        for (int i = 0; i < (int)points.size() - 1; i++) {
            Engine::Get().GetRenderer().SetColor(0.5f, 0.2f, 0.4f);
            Engine::Get().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }
        // character
        scene.Draw(Engine::Get().GetRenderer());
        
        // PRESENT
        Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    

    return 0;
}