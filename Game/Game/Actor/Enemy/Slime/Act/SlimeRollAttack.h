#pragma once

#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class SlimeRollAttack : public EnemyAct{
public:
	SlimeRollAttack();

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;

private:
	bool rolling = false;
	float rollTimer = 3.0f;
	float damageCool = 0;

	float m_soundTimer = 0.0f;
	SoundOverlap m_sound;
};

}
