// Files use namespace fe::

#include "Engine.h"
#include "SpaceGame.h"
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

    /*Factory::Instance().Register<Actor>("Actor");
    auto actor = Factory::Instance().Create<Actor>("Actor");

    return 0;*/

            
    // ENGINE INITIALIZATION / SET DIRECTORY
    Engine::Get().Initialize();
    fe::SetWorkingDirectory("Assets");

    // load the json data from a file
    std::string buffer;
    if (fe::ReadTextFile("data/data.json", buffer))
    {
        // show the contents of the json file (debug)
        std::cout << buffer << std::endl;

        // create json document from the json file contents
        rapidjson::Document document;
        if (json::Load("Data/data.json", document))
        {
            // read the age data (int) from the json
            std::string name;
            int age;            
            float speed;
            bool isAwake;
            nu::Vector2 position;
            nu::Vector3 color;

            json::Read(document, "age", age);
            // show the age data
            std::cout << age << std::endl;

            // read the json data
            JSON_READ(document, name);
            JSON_READ(document, age);
            JSON_READ(document, speed);
            JSON_READ(document, isAwake);
            JSON_READ(document, position);
            JSON_READ(document, color);

            // show the data
            std::cout << name << " " << age << " " << speed << " " << isAwake << std::endl;
            std::cout << position.x << " " << position.y << std::endl;
            std::cout << color.r << " " << color.g << " " << color.b << " " << std::endl;
        }        
    }

    return 0;

    // SPACE GAME INITIALIZATION
    SpaceGame game;
    game.Initialize();

    // create texture, using shared_ptr so texture can be shared
    std::shared_ptr<Texture> texture = std::make_shared<Texture>();
    texture->Load("Images/large_grey_01.png", Engine::Get().GetRenderer());

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
        auto texture = Resources().Get<Texture>("Images/large_grey_01.png", Engine::Get().GetRenderer());
        Engine::Get().GetRenderer().DrawTexture(*texture, 30, 30, 23.0f, 2.0f);
        
        // PRESENT
        Engine::Get().GetRenderer().Present();
    }

    // SHUTDOWN
    Engine::Get().Shutdown();
    

    return 0;
}