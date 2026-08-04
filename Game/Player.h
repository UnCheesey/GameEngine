#pragma once
#include "Actor.h"

struct PlayerDesc : public nu::ActorDesc {
    float speed;
};

enum class WeaponState {
    Default,
    Multishot,
    Rapid,
    Rocket,
};

class Player : public nu::Actor{
public:
    Player() = default;

    Player(const PlayerDesc& playerDesc) :
        Actor(playerDesc),
        m_speed(playerDesc.speed) {
    }


    void SetWeaponState(WeaponState weaponState) { m_weaponState = weaponState; }
    WeaponState GetWeaponState() const { return m_weaponState; }
       
    void Update(float dt) override;
    void SpawnBullet(float speed, float offset = 0.0f, float lifespan = 1.0f);
    void SpawnRocket(float speed, int pellet = 5, float rocketLifeSpan = 1.0f, float pelletLifeSpan = 2.0f);

    void Fire();
    void OnCollision(Actor* other) override;

    std::string WeaponToString();

private:
    WeaponState m_weaponState = WeaponState::Default;
    float m_fireTimer = 0.0f;
	int m_ammo = 0;
    float m_speed = 800.0f;
};