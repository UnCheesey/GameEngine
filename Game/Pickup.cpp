#include "Pickup.h"

void Pickup::OnCollision(Actor* actor) {
	if (actor->GetTag() == "Player") {
		Player* player = dynamic_cast<Player*>(actor);
		player->SetWeaponState(m_weaponType);

		SetDestroyed();
	}
}
