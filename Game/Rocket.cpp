#include "Rocket.h"
#include "Scene.h"
#include "Factory.h"

FACTORY_REGISTER(Rocket)

Rocket::~Rocket() {
	Explode();
}

void Rocket::Explode() {

    float angle = 360.0f / static_cast<float>(m_pelletAmount);

    for (int i = 0; i < m_pelletAmount; ++i) {
        BulletDesc pelletDesc = m_pelletDesc;

        pelletDesc.transform = m_transform;

        pelletDesc.transform.rotation = i * angle;

        m_scene->AddActor(std::move(std::make_unique<Bullet>(pelletDesc)));
    }
}
