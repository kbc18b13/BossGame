#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

class ModelArmWeapon;

namespace EnemySpace{

class SkeJumpAttack : public EnemyAct{
public:
	SkeJumpAttack( ModelArmWeapon& sword );
	virtual ~SkeJumpAttack();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

	void End( Actor* s ) override;

	virtual void Init( SkinModelRender* model, CharaConEx* chara, Actor* target );

private:
	ModelArmWeapon& m_sword;
};

}