#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"

void Enemy::Update(float dt) {
    Player* player = m_scene->GetActorByName<Player>("Player");
    if (player) {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    //if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;
    
    //SetRotation(m_transform.rotation +  rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    Actor::Update(dt);
}