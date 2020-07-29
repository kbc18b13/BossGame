#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class ArmWeapon;

namespace EnemySpace{

class TrollAttack : public EnemyAct{
public:
	TrollAttack( ArmWeapon& arm );

	void Init( SkinModelRender* model, CharaConEx* chara, Actor* target )override;

	void SubStart(Actor* a) override;
	void Update( Actor* a ) override;
	void End( Actor* a ) override;

private:
	bool m_isSecond = false;
	ArmWeapon& m_arm;
};

}