#include "pch.h"
#include "Scene.h"
#include "Actor.h"
#include "Factory.h"


namespace nu {
	void Scene::AddActor(std::unique_ptr<Actor> actor){
		actor->m_scene = this;
		m_pendingActors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors() {
		m_actors.clear();
	}

	bool Scene::Load(const std::string& sceneName) {
		json::document_t document;
		if (json::Load("data/scene.json", document)) {
			if (JSON_HAS_NAME(document, "actors")) {
				for (auto& actorValue : JSON_GET_NAME(document, "actors").GetArray()) {

					// get actor type
					std::string typeName;
					JSON_READ_NAME(actorValue, "type", typeName);

					std::cout << "Loading actor type: " << typeName << std::endl;

					// create actor of type
					auto actor = Factory::Instance().Create<Actor>(typeName);

					if (!actor) {
						std::cout << "Could not create actor type: " << typeName << std::endl;
						continue;
					}

					// read actor json
					actor->Read(actorValue);

					// check if prototype
					bool prototype = false;
					JSON_READ(actorValue, prototype);

					if (prototype) {
						// if prototype, add prototype to factory registry
						std::string name;
						JSON_READ(actorValue, name);
						Factory::Instance().RegisterPrototype<Actor>("PlayerPrototype", std::move(actor));
					}
					else {
						AddActor(std::move(actor));
					}
				}
			}
			return true;
		}
		else {
			return false;
		}
	}

	void Scene::Update(float dt) {
		// UPDATE ACTORS
		for (auto& actor : m_actors) {
			actor->Update(dt);
		}

		// UPDATE COLLISIONS
 		UpdateCollisions();

		// REMOVE DESTROYED ACTORS
		std::erase_if(m_actors, [](auto& actor) {
			return actor->m_destroyed;
		});

		// ADD PENDING ACTORS
		for (auto& actor : m_pendingActors) {
			m_actors.push_back(std::move(actor));
		}
		m_pendingActors.clear();
	}

	void Scene::Draw(const class Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	void Scene::UpdateCollisions() {
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || actorA->m_destroyed || actorB->m_destroyed) continue;

				float distance = (actorA->m_transform.position - actorB->m_transform.position).Length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}

	}
}