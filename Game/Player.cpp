#include "Player.h"
#include "Bullet.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"

void Player::Update(float dt) {

    // MOVEMENT
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) thrust = +m_speed;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;
    
    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    // FIRE

    if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
        BulletDesc bulletDesc;
        bulletDesc.name = "bullet";
        bulletDesc.tag = "bullet";
        bulletDesc.model = assets::bulletModel;
        bulletDesc.transform = m_transform;
        bulletDesc.speed = 1000.0f;
        bulletDesc.lifespan = 2.0f;

        Bullet* bullet = new Bullet(bulletDesc);
        m_scene->AddActor(bullet);
    }

    Actor::Update(dt);
}