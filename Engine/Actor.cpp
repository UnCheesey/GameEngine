#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"

namespace nu {

    void Actor::Update(float dt) {

        //LIFESPAN
        if (m_lifespan > 0.0f) {
            m_lifespan -= dt;
            m_destroyed = (m_lifespan <= 0.0f);
        }

        // MOVEMENT
        m_transform.position += (m_velocity * dt);
        m_velocity *= 1.0f / (1.0f + m_damping * dt);

        m_transform.position.x = Clamp(0.0f, 1920.0f, m_transform.position.x);
        m_transform.position.y = Clamp(0.0f, 1024.0f, m_transform.position.y);
    }

    void Actor::Draw(const Renderer& render) const {
        if (m_model) {
            render.DrawModel(*m_model, m_transform);
        }
    }

    float Actor::GetRadius() const
    {
        return m_model->GetRadius() * m_transform.scale * 0.95f;
    }
}