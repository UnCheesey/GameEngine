#include "Enemy.h"
#include "Player.h"
#include "Renderer.h"
#include "Engine.h"
#include "SpaceGame.h"

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt) {
    Player* player = m_scene->GetActorByTag<Player>("Player");
    if (player) {
        nu::Vector2 direction = player->GetTransform().position - m_transform.position;
        float rotation = direction.Angle();
        SetRotation(rotation * nu::RadToDeg);

        nu::Vector2 forward{ 1, 0 };
        forward = forward.Rotate(m_transform.rotation * nu::DegToRad);
        AddVelocity(forward * m_speed * dt);
    }

    float thrust = 0.0f;

    float rotate = 0.0f;

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    Actor::Update(dt);
}

void Enemy::Read(const json::value_t& value) {
    /*JSON_READ_NAME(value, "points", );
    JSON_READ_NAME(value, "health", );*/
    JSON_READ_NAME(value, "speed", m_speed);
}

void Enemy::OnCollision(Actor* other) {
    if (other->GetTag() == "Bullet" || other->GetTag() == "Rocket") {
        SetDestroyed();
        other->SetDestroyed();

        ((SpaceGame*)m_scene->GetGame())->AddPoints(100);

        for (int i = 0; i < 100; i++)
        {
            nu::Particle particle;
            particle.position = m_transform.position;
            particle.color = { nu::RandomColor(), nu::RandomColor(), nu::RandomColor() };
            particle.lifespan = nu::RandomFloat(0.5f, 2.0f);
            particle.velocity = { nu::RandomFloat(-600.0f, 600.0f), nu::RandomFloat(-600.0f, 600.0f) };

            nu::Engine::Get().GetParticleSystem().AddParticle(particle);
        }
    }
}
