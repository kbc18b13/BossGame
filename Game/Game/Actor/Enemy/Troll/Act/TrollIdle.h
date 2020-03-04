#pragma once
#include "Actor\Enemy\Act\EnemyAct.h"

namespace EnemySpace{

class TrollIdle : public EnemyAct{
public:
	TrollIdle();
	void SubStart( Actor* t ) override;
	void Update( Actor* t ) override;
private:
	float m_timer = 0;
};

}