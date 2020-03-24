#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

class ArmWeapon;

namespace EnemySpace{

class SlimeStrike : public EnemyAct{
public:
	SlimeStrike(ArmWeapon& weapon) : m_weapon(weapon){}

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;

private:
	ArmWeapon& m_weapon;
};

}
