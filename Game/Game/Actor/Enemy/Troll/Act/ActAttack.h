#pragma once
#include "Act.h"

class ArmWeapon;

namespace TrollAct{

class ActAttack : public Act{
public:
	ActAttack( ArmWeapon& arm );
	void Start(Troll* t) override;
	void Continue( Troll* t ) override;

private:
	bool m_isAttack = false;
	float m_timer = 0.0f;
	ArmWeapon& m_arm;
};

}