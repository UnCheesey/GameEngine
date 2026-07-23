#pragma once
#include "Actor.h"

#include <vector>
#include <string>

namespace nu {
	class Scene {
		
	public:
		void AddActor(Actor* actor);

		void Update(float dt);
		void Draw(const class Renderer& renderer);

		template<typename T>
		T* GetActorByName(const std::string& name);

	private:
		std::vector<Actor*> m_actors;
		std::vector<Actor*>m_pendingActors;
	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto actor : m_actors) {
			T* actorT = dynamic_cast<T*>(actor);
			if (actorT && actorT->m_name == name) {
				return actorT;
			}
		}

		return nullptr;
	}
}