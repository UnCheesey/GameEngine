#pragma once
#include "Actor.h"

struct BulletDesc : public nu::ActorDesc {
    float speed;
};

class Bullet : public nu::Actor {
public:
    Bullet() = default;

    Bullet(const BulletDesc& bulletDesc) :
        Actor(bulletDesc),
        m_speed(bulletDesc.speed) {
    }


    void Update(float dt) override;

protected:
    float m_speed = 100.0f;
};