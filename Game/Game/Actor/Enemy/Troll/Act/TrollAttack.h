#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class ArmWeapon;

namespace EnemySpace{

class TrollAttack : public EnemyAct{
public:
	TrollAttack( ArmWeapon& arm );
	void SubStart(Actor* a) override;
	void Update( Actor* a ) override;

private:
	bool m_isAttack = false;
	float m_timer = 0.0f;
	ArmWeapon& m_arm;
};

}