#pragma once
#include "Bullet.h"

struct RocketDesc : public BulletDesc {
	int pelletAmount;
	BulletDesc pelletDesc;
};

class Rocket : public Bullet {
public:
	Rocket() = default;
	Rocket(const RocketDesc& rocketDesc) :
		Bullet(rocketDesc),
		m_pelletDesc(rocketDesc.pelletDesc),
		m_pelletAmount(rocketDesc.pelletAmount)
	{}
	~Rocket() override;

	CLASS_PROTOTYPE(Rocket)

private:
	void Explode();

	int m_pelletAmount;
	BulletDesc m_pelletDesc;

};
