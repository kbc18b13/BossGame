#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class YowaIdle : public EnemyAct{
public:
	YowaIdle();
	virtual ~YowaIdle();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

private:
	float m_timer = 0;
};

}