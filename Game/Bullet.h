#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc {
    float speed;
};

class Bullet : public nu::Actor {
public:
    Bullet() = default;

    Bullet(const BulletDesc& enemyDesc) :
        Actor(enemyDesc),
        m_speed(enemyDesc.speed) {
    }

    Bullet(const nu::Transform& transform, const nu::Model& model) :
        Actor(transform, model) {
    }

    Bullet(float speed, const nu::Transform& transform, const nu::Model& model) :
        m_speed(speed),
        Actor(transform, model) {
    }

    void Update(float dt) override;

private:
    float m_speed = 100.0f;
};