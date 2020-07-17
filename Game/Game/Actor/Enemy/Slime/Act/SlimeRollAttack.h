#pragma once

#include "Actor/Enemy/Act/EnemyAct.h"
#include "physics/CollisionObject.h"
#include "physics/CylinderCollider.h"

namespace EnemySpace{

class SlimeRollAttack : public EnemyAct{
public:
	void Init( SkinModelRender* model, CharaConEx* chara, Actor* target ) override;

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;
	void End( Actor* a )override;

private:
	bool rolling = false;
	float rollTimer = 3.0f;
	float damageCool = 0;

	float m_soundTimer = 0.0f;
	SoundOverlap m_sound;

	CylinderCollider m_rollShape;
	CollisionObject m_rollColl;
};

}
