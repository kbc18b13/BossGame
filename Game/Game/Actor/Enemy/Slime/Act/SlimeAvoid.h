#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class SlimeAvoid : public EnemyAct{
public:
	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;

private:
	CVector3 m_moveVec;
};

}
