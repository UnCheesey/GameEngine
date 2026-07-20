#include "pch.h"
#include "Scene.h"
#include "Actor.h"


namespace nu {
	void Scene::Update(float dt) {
		for (auto actor : m_actors) {
			actor->Update(dt);
		}
	}
	void Scene::Draw(const class Renderer& renderer) {
		for (auto actor : m_actors) {
			actor->Draw(renderer);
		}
	
	}
}