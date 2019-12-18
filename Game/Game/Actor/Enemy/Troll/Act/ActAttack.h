#pragma once
#include "Act.h"

class TrollArmCollision;

namespace TrollAct{

class ActAttack : public Act{
public:
	ActAttack( TrollArmCollision& arm );
	void Start(Troll* t) override;
	void Continue( Troll* t ) override;

private:
	bool m_isAttack = false;
	float m_timer = 0.0f;
	TrollArmCollision& m_arm;
};

}