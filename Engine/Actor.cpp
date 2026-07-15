#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

namespace nu {

    void Actor::Update(float dt) {
        m_transform.position += (m_velocity * dt);
        m_velocity *= 0.987f;

        m_transform.position.x = Wrap(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Wrap(0.0f, 1024.0f, m_transform.position.y);

    }

    void Actor::Draw(const Renderer& render) const {
        render.DrawModel(m_model, m_transform);
    }

}