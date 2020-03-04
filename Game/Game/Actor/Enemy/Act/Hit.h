#pragma once
#include "Actor/Enemy/Act/EnemyAct.h"

namespace EnemySpace{

class Hit : public EnemyAct{
public:
	Hit(int animation, int nextState);
	virtual ~Hit();

	void SubStart( Actor* s ) override;
	void Update( Actor* s ) override;

private:
	int m_anim;
	int m_next;
};

}
