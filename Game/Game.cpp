#include "Engine.h"

#include <iostream>
#include <vector>

using namespace nu;

struct Transform {
    Vector2 position;
    float rotation;
    float scale;
};

class Actor {
public:
    Actor() = default;
    Actor(const Transform& transform) : m_transform(transform){}

    void Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.99f;

        m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);

    }

    void Draw(const Renderer& render) const {
        render.SetColor(1.0f, 1.0f, 1.0f);
        render.DrawFillRect(m_transform.position.x - (m_transform.scale * 0.5f), m_transform.position.y - (m_transform.scale * 0.5f), m_transform.scale, m_transform.scale);
    }

    const Transform& GetTransform() const {return m_transform;}

    void SetPosition(const Vector2& position) { m_transform.position = position; }
    void SetRotation(float rotation) { m_transform.rotation = rotation; }
    void SetScale(float scale) { m_transform.scale = scale; }

    const Vector2& GetVelocity() const { return m_velocity; }
    void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }

protected:
    Transform m_transform;
    Vector2 m_velocity{ 0, 0 };
};

int main() {
    // INITIALIZATION
    Renderer render;
    render.Initialize("Game Engine", 1920, 1024);

    nu::Input input;
    input.Initialize();

    nu::Time time;

    Actor player( Transform ( Vector2 { 640.0f, 512.0f }, 0.0f, 50.0f ) );

    int speed = 400;
    Vector2 position{ 640, 512 };
    Vector2 velocity{ 0.0f, 0.0f };
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