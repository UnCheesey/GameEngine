#include "Player.h"
#include "Rocket.h"
#include "Assets.h"
#include "Renderer.h"
#include "Engine.h"

void Player::Update(float dt) {

    // MOVEMENT
    float thrust = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_W)) { 
        thrust = +m_speed; 
        // PARTICLES
        nu::Particle particle;
        particle.position = m_transform.position;
        particle.color = { nu::RandomColor(), nu::RandomColor(), nu::RandomColor() };
        particle.lifespan = nu::RandomFloat(0.5f, 1.5f);
        particle.velocity = { nu::RandomFloat(-200.0f, 200.0f), nu::RandomFloat(-50.0f, 50.0f) };

        nu::Engine::Get().GetParticleSystem().AddParticle(particle);
    }
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_S)) thrust = -m_speed;

    float rotate = 0.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -180.0f;
    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = +180.0f;
    
    SetRotation(m_transform.rotation + rotate * dt);

    nu::Vector2 forward{ 1, 0 }; // ->
    nu::Vector2 velocity = forward.Rotate(m_transform.rotation * nu::DegToRad) * thrust;
    AddVelocity(velocity * dt);

    // FIRE
    Fire();
    

    if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_X)) {
        nu::Engine::Get().GetTime().SetTimeScale(0.5f);
    }else {
        nu::Engine::Get().GetTime().SetTimeScale(1.0f);
    }

    

    Actor::Update(dt);
}

void Player::SpawnBullet(float speed, float offset, float lifespan) {
    BulletDesc bulletDesc;
    bulletDesc.name = "Bullet";
    bulletDesc.tag = "PlayerBullet";
    bulletDesc.model = assets::bulletModel;
    bulletDesc.transform = m_transform;
    bulletDesc.transform.scale *= 0.8f;
    bulletDesc.speed = speed;
    bulletDesc.lifespan = lifespan;
    bulletDesc.transform.rotation += offset;
    
    nu::Engine::Get().GetAudio().PlaySound("laser");
    m_scene->AddActor(std::move(std::make_unique<Bullet>(bulletDesc)));
}

void Player::SpawnRocket(float speed, int pellet, float rocketLifeSpan, float pelletLifeSpan) {
    BulletDesc pelletDesc;
    pelletDesc.name = "Pellet";
    pelletDesc.tag = "PlayerBullet";
    pelletDesc.model = assets::bulletModel;
    pelletDesc.transform = m_transform;
    pelletDesc.speed = speed;
    pelletDesc.lifespan = pelletLifeSpan;
    pelletDesc.transform.scale *= 0.3f;

    RocketDesc rocketDesc;
    rocketDesc.name = "Rocket";
    rocketDesc.tag = "PlayerRocket";
    rocketDesc.model = assets::bulletModel;
    rocketDesc.transform = m_transform;
    rocketDesc.speed = speed * 1.5f;
    rocketDesc.lifespan = rocketLifeSpan;
    rocketDesc.pelletDesc = pelletDesc;
    rocketDesc.pelletAmount = pellet;

    nu::Engine::Get().GetAudio().PlaySound("laser");
    m_scene->AddActor(std::move(std::make_unique<Rocket>(rocketDesc)));
}

void Player::Fire() {
    switch (m_weaponState) {
    case WeaponState::Default:
        m_fireTimer -= nu::Engine::Get().GetTime().GetDeltaTime();
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_fireTimer <= 0.0f) {
            SpawnBullet(m_speed * 0.5f);
            m_fireTimer = 0.35f;
        }
        break;
    case WeaponState::Rapid:
        m_fireTimer -= nu::Engine::Get().GetTime().GetDeltaTime();
        if (nu::Engine::Get().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && m_fireTimer <= 0.0f) {
            SpawnBullet(m_speed * 0.5f);
            m_fireTimer = 0.15f;
        }
        break;
    case WeaponState::Multishot:
        m_fireTimer -= nu::Engine::Get().GetTime().GetDeltaTime();
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_fireTimer <= 0.0f) {
            SpawnBullet(m_speed * 0.5f);
            SpawnBullet(m_speed * 0.5f, 10.0f);
            SpawnBullet(m_speed * 0.5f, -10.0f);
            m_fireTimer = 0.35f;
        }
        break;
    case WeaponState::Rocket:
        m_fireTimer -= nu::Engine::Get().GetTime().GetDeltaTime();
        if (nu::Engine::Get().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE) && m_fireTimer <= 0.0f) {
            SpawnRocket(m_speed * 0.2f, 10, 1.0f, 1.5f);
            m_fireTimer = 0.85f;
        }
        break;
    default:
        break;
    }
}

void Player::OnCollision(Actor* other) {
    if (other->GetTag() == "Enemy") {
        SetDestroyed();
        other->SetDestroyed();
    }
}

std::string Player::WeaponToString()
{
    switch (m_weaponState) {
    case WeaponState::Default: return "Default";
    case WeaponState::Multishot:  return "Multishot";
    case WeaponState::Rapid:   return "Rapid";
    case WeaponState::Rocket:  return "Rocket";
    default:                   return "Unknown";
    }
}
