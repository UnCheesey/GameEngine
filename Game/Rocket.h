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

private:
	void Explode();

	int m_pelletAmount = 5;
	BulletDesc m_pelletDesc;

};
