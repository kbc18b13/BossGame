#pragma once
#include "EnemyAct.h"
class Player;

namespace EnemySpace{

class SideWalk : public EnemyAct{
public:
	SideWalk( int walkAnim, int nextState);
	~SideWalk();

	void SubStart( Actor* a ) override;

	void Update( Actor* a ) override;

private:
	int m_nextState;
	int m_walkAnim;
	float m_timer = 0.0f;
};

}