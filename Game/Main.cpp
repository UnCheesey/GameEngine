// Files use namespace fe::

#include "Engine.h"
#include "SpaceGame.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <map>

using namespace nu;

//class Animal {
//
//public:
//    virtual void Speak() {
//        std::cout << "Animal speaks" << std::endl;
//    }
//};
//
//class Cat : public Animal {
//    void Speak() override {
//        std::cout << "Meow" << std::endl;
//    }
//};
//
//class Dog : public Animal {
//    void Speak() override {
//        std::cout << "Woof" << std::endl;
//    }
//};
//
//class Bird : public Animal {
//    void Speak() override {
//        std::cout << "Chirp" << std::endl;
//    }
//};
//
//Animal* AnimalFactory(const std::string& id) {
//    Animal* animal = nullptr;
//
//    if (nu::ToLower(id) == "cat") animal = new Cat;
//    else if (nu::EqualsIgnoreCase(id, "Dog")) animal = new Dog;
//    else if (id == "Bird") animal = new Bird;
//
//    return animal;
//}

int main() {
    fe::SetWorkingDirectory("Assets");

    Factory::Instance().Register<Actor>("Actor");
    Factory::Instance().Register<Object>("Object");
    Factory::Instance().Register<Player>("Player");

    auto actor = Factory::Instance().Create<Actor>("Actor");
    std::cout << actor->IsActive() << std::endl;
    
    auto object = Factory::Instance().Create("Object");
    std::cout << object->IsActive() << std::endl;

    auto player = Factory::Instance().Create<Player>("Player");
    std::cout << player->IsActive() << std::endl;


    json::document_t document;
    if (json::Load("Data/scene.json", document)) {

        player->Read(document);
        std::cout << "Name: " << player->GetName() << std::endl;
        std::cout << "Active: " << player->IsActive() << std::endl;
        std::cout << "Tag: " << player->GetTag() << std::endl;
        std::cout << "Speed: " << player->GetSpeed() << std::endl;

        std::cout << "Rotation: " << player->GetTransform().rotation << std::endl;
        std::cout << "Scale: " << player->GetTransform().scale << std::endl;
    }

    return 0;

            
    // ENGINE INITIALIZATION / SET DIRECTORY
    Engine::Get().Initialize();
    fe::SetWorkingDirectory("Assets");
        
    // SPACE GAME INITIALIZATION
    SpaceGame game;
    game.Initialize();

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
        
        // ENGINE UPDATE (audio, input, time)
        Engine::Get().Update();
        float dt = Engine::Get().GetTime().GetDeltaTime();
        game.Update(dt);
                        
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