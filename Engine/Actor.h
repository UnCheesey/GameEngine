#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>

namespace nu {
    struct ActorDesc {
        std::string name;
        std::string tag;
        Transform transform;
        Vector2 velocity;
        Model model;

    };

    class Actor {
    public:
        Actor() = default;
        Actor(const ActorDesc& actorDesc) :
            m_tag(actorDesc.tag),
            m_name(actorDesc.tag),
            m_transform(actorDesc.transform),
            m_velocity(actorDesc.velocity),
            m_model(actorDesc.model){
        }

        Actor(const Transform& transform) : m_transform(transform) {}


        Actor(const Transform& transform, const Model& model) :
            m_transform(transform),
            m_model(model)
        {}

        virtual void Update(float dt);
        virtual void Draw(const class Renderer& render) const;

        const Transform& GetTransform() const { return m_transform; }
        void SetPosition(const Vector2& position) { m_transform.position = position; }
        void SetRotation(float rotation) { m_transform.rotation = rotation; }
        void SetScale(float scale) { m_transform.scale = scale; }

        const Vector2& GetVelocity() const { return m_velocity; }
        void SetVelocity(const Vector2& velocity) { m_velocity = velocity; }
        void AddVelocity(const Vector2& velocity) { m_velocity += velocity; }
        const std::string& GetName() const { return m_name; }
        const std::string& GetTag() const { return m_tag; }

    protected:
        std::string m_name;
        std::string m_tag;

        Transform m_transform;
        Vector2 m_velocity{ 0, 0 };

        Model m_model;
    };
}