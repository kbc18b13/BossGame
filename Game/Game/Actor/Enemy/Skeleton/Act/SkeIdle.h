#pragma once
#include "..\SkeletonEnemy.h"
#include "Actor\Enemy\Act\EnemyAct.h"

namespace EnemySpace{

class SkeIdle : public EnemyAct{
public:
	SkeIdle();
	virtual ~SkeIdle();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

private:
	float m_timer;
};

}

