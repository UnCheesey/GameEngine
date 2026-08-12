#include "pch.h"
#include "Actor.h"
#include "Renderer.h"
#include "MathUtils.h"
#include "Texture.h"
#include "Model.h"

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
        if (m_texture) {
            render.DrawTexture(*m_texture, m_transform.position.x, m_transform.position.y, m_transform.rotation, m_transform.scale);
        }
    }

    float Actor::GetRadius() const {
        if (m_model) return m_model->GetRadius() * m_transform.scale * 0.07f;

        if (m_texture) 
            return (m_texture->GetSize().Length() * m_transform.scale * 0.5f) * 0.5f;

        return 0.0f;
    }

    void Actor::Read(const json::value_t& value) {

        Object::Read(value);

        if (JSON_HAS_NAME(value, "transform")) {
            m_transform.Read(JSON_GET_NAME(value, "transform"));
        }

        JSON_READ_NAME_REQ(value, "tag", m_tag);
        JSON_READ_NAME_REQ(value, "lifespan", m_lifespan);
        JSON_READ_NAME_REQ(value, "velocity", m_velocity);
        JSON_READ_NAME_REQ(value, "damping", m_damping);
    }
}