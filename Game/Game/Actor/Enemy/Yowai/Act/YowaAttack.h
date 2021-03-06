#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

class ArmWeapon;

namespace EnemySpace{

class YowaAttack : public EnemyAct{
public:
	YowaAttack(ArmWeapon& weapon);
	~YowaAttack();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;
	void End( Actor* s ) override;

	void Init( SkinModelRender* model, CharaConEx* chara, Actor* target ) override;

private:
	ArmWeapon& m_weapon;
};

}