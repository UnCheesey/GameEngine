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

    CLASS_PROTOTYPE(Bullet)


    void Update(float dt) override;

    void Read(const json::value_t& value) override;

protected:
    float m_speed = 100.0f;
};