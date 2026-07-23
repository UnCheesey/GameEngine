#pragma once
#include "Actor.h"

struct EnemyDesc : public nu::ActorDesc {
    float speed;
};

class Enemy : public nu::Actor {
public:
    Enemy() = default;

    Enemy(const EnemyDesc& enemyDesc) :
        Actor(enemyDesc),
        m_speed(enemyDesc.speed) {
    }

    Enemy(const nu::Transform& transform, const nu::Model& model) : 
        Actor(transform, model) {
    }

    Enemy(float speed, const nu::Transform& transform, const nu::Model& model) : 
        m_speed(speed), 
        Actor(transform, model) {
    }

    void Update(float dt) override;

private:
    int m_ammo = 0;
    float m_speed = 800.0f;
};