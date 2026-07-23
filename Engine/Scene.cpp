#include "pch.h"
#include "Scene.h"
#include "Actor.h"


namespace nu {
	void Scene::AddActor(Actor* actor){
		actor->m_scene = this;
		m_pendingActors.push_back(actor);
	}

	void Scene::Update(float dt) {
		// UPDATE ACTORS
		for (auto actor : m_actors) {
			actor->Update(dt);
		}

		// REMOVE DESTROYED ACTORS
		std::erase_if(m_actors, [](auto actor) { return actor->m_destroyed; });

		// ADD PENDING ACTORS
		m_actors.insert(m_actors.end(), m_pendingActors.begin(), m_pendingActors.end());
		m_pendingActors.clear();
	}
	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	
	}
}