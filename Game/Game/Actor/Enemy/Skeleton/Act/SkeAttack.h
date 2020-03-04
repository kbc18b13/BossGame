#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class ModelArmWeapon;

namespace EnemySpace{

class SkeAttack : public EnemyAct{
public:
	SkeAttack(ModelArmWeapon& sword, int animation, int maxCombo);
	virtual ~SkeAttack();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

	void End( Actor* s ) override;

private:
	ModelArmWeapon& m_sword;
	int m_anim;
	int m_maxCombo;
	int m_nowCombo;
};

}

