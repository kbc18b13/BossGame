#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class SlimeStrike : public EnemyAct{
public:
	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;
};

}
