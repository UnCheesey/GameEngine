#include "Player.h"
#include "Renderer.h"
#include "Engine.h"

void Player::Update(float dt) {
    nu::Vector2 force{ 0.0f, 0.0f };
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_W)) force.y = -m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_A)) force.x = -m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_S)) force.y = +m_speed;
    if (nu::engine.GetInput().GetKeyDown(SDL_SCANCODE_D)) force.x = +m_speed;

    SetVelocity(GetVelocity() + (force * dt));

    Actor::Update(dt);
}

void Player::Draw(const nu::Renderer& render) const {
	Actor::Draw(render);

}