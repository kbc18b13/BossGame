#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class ModelArmWeapon;

namespace EnemySpace{

class SkeAttack : public EnemyAct{
public:
	SkeAttack(ModelArmWeapon& sword, int animation);
	virtual ~SkeAttack();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

private:
	ModelArmWeapon& m_sword;
	int m_anim;
};

}

