#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"
#include "physics/CollisionObject.h"
#include "physics/CylinderCollider.h"

namespace EnemySpace{

class SlimeIdle : public EnemyAct{
public:
	SlimeIdle();
	~SlimeIdle();

	void SubStart( Actor* a ) override;
	void Update( Actor* a ) override;

private:
	float m_timer = 0;
	CylinderCollider m_rollShape;
	CollisionObject m_rollColl;
};

}