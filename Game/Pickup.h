#pragma once
#include "Actor.h"
#include "Player.h"
#include "Random.h"

class Pickup : public nu::Actor {
public:
	Pickup() = default;
	Pickup(const nu::ActorDesc& actorDesc) : Actor(actorDesc) {
		m_weaponType = static_cast<WeaponState>(nu::RandomInt(4));
	}

	void OnCollision(Actor* actor) override;
private:
	WeaponState m_weaponType = WeaponState::Default;

};
